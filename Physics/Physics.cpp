#include "Physics.h"

#include <Components/Transform.h>
#include <Physics/Collider.h>
#include <Physics/AABB.h>
#include <Physics/MPR.h>
#include <Physics/Solver.h>
#include <Physics/SolverManager.h>
#include <GameObject.h>
#include <WaltEngine.h>

using namespace walt;
using namespace glm;
using namespace std;

Physics::Physics()
{
    solverManager = new SolverManager();
}

Physics::~Physics()
{
    delete solverManager;
}

void Physics::update()
{
    instance.updateAll();
}

void Physics::updateAll()
{
    elapsedStepSeconds = WaltEngine::elapsedSeconds / numSteps;
    elapsedStepTicks = WaltEngine::elapsedTicks / numSteps;
    timeRatio = WaltEngine::timeRatio;

    for (auto& collider : colliders)
    {
        if (collider->dynamic) {
            collider->netForce += gravity * collider->mass();
        }
    }

    for (int step = 0; step < numSteps; ++step)
    {
        totalSeconds += elapsedStepSeconds;
        totalTicks += elapsedStepTicks;

        for (auto& collider : colliders)
        {
            collider->updatePhysics();

            collider->velocity *= friction;
            collider->angularVelocity *= 0.9999999999f;
        }

        vec3 worldA, worldB, normal;

        for (auto x = colliders.begin(); x != colliders.end();)
        {
            auto& colliderA = **x;
            for (auto y = ++x; y != colliders.end(); ++y)
            {
                auto& colliderB = **y;

                if (!AABB::FindCollision(colliderA, colliderB)) continue;

                if (!MPR::FindCollision(colliderA, colliderB, worldA, worldB, normal)) {
                    continue;
                }

                auto tmp = -normal;
                vec3 supportA = colliderA.findSupport(tmp);
                vec3 supportB = colliderB.findSupport(normal);

                worldA = dot(supportA - worldA, normal) * normal + worldA;
                worldB = dot(supportB - worldB, normal) * normal + worldB;

                auto solver = solverManager->getSolver(&colliderA, &colliderB);
                solver->addContact(worldA, worldB, normal);
            }
        }

        // Collision response
        solverManager->update();
    }

    for (auto& collider : colliders)
    {
        collider->netForce = vec3();
        collider->netTorque = vec3();
    }
}

void Physics::add(Collider* collider)
{
    instance.colliders.push_back(collider);
}

void Physics::remove(Collider* collider)
{
    instance.colliders.remove(collider);
}

Physics Physics::instance;

vec3 Physics::gravity = vec3(0, -9.8, 0);
float Physics::friction = 0.99f;
int Physics::numSteps = 2;
float Physics::effectiveMassFactor = 1.f;
float Physics::betaFactor = .5f;
float Physics::positionErrorDiminish = -1.f;
int Physics::numSolverIteration = 10;

float Physics::elapsedStepSeconds;
long long Physics::elapsedStepTicks;
float Physics::totalSeconds;
long long Physics::totalTicks;
float Physics::timeRatio;
