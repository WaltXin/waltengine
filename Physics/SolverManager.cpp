#include "SolverManager.h"

#include <Components/Transform.h>
#include <Physics/Collider.h>
#include <Physics/Physics.h>
#include <Physics/Solver.h>
#include <Physics/SolverKey.h>
#include <GameObject.h>

using namespace walt;
using namespace glm;
using namespace std;

SolverManager::SolverManager()
{
}

SolverManager::~SolverManager()
{
}

Solver* SolverManager::getSolver(Collider* a, Collider* b)
{
    auto key = SolverKey::get(a, b);
    auto* solver = solvers[key];

    if (solver == nullptr)
    {
        solver = new Solver(this, a, b);
        solvers[key] = solver;
    }

    return solver;
}

void SolverManager::addContact(Collider* a, Collider* b, glm::vec3& worldA, glm::vec3& worldB, glm::vec3& normal)
{
    auto solver = getSolver(a, b);
    solver->addContact(worldA, worldB, normal);
}

void SolverManager::update()
{
    int i = iteration;

    for (iteration = 0; iteration < Physics::numSolverIteration; iteration++)
    {
        for (auto& solver : solvers)
        {
            solver.second->update();
        }
    }
}
