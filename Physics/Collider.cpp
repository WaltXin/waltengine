#include "Collider.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <Components/Transform.h>
#include <Physics/Physics.h>
#include <Physics/AABB.h>
#include <Physics/Contact.h>
#include <GameObject.h>

using namespace walt;
using namespace glm;
using namespace std;

Collider::Collider()
{
    id = ++prevId;

    if (id > MaxId) {
        fprintf(stderr, "Exceed allowed max number of colliders\n");
        throw 1;
    }

    Physics::add(this);
    aabb = new AABB();

    inverseMass = value_attr<float>(
        [this]() -> float { return _inverseMass; },
        [this](float value) {
            _inverseMass = value;
            updateInetiaTensor();
        }
    );

    mass = value_attr<float>(
        [this]() -> float { return 1.f / inverseMass; },
        [this](float value) { inverseMass = 1.f / value; }
    );

    dynamic = value_attr<bool>(
        [this]() -> const bool { return inverseMass != 0; },
        [this](bool value) { inverseMass = value ? 1.f : 0; }
    );

    kinematic = value_attr<bool>(
        [this]() -> const bool { return inverseMass == 0; },
        [this](bool value) { inverseMass = value ? 0 : 1.f; }
    );

    computedInverseMass = value_attr<float>(
        [this]() -> const float { return dynamic ? inverseMass : 0; }
    );
}

Collider::~Collider()
{
    Physics::remove(this);
}

glm::mat4 Collider::getInertiaTensor()
{
    return glm::inverse(inverseInertiaTensor);
}

void Collider::setInertiaTensor(glm::mat4& value)
{
    inverseInertiaTensor = glm::inverse(value);
}

glm::mat4 Collider::getInverseWorldInertiaTensor()
{
    mat4 rotationMatrix = toMat4(transform->rotation);
    return rotationMatrix * inverseInertiaTensor * transpose(rotationMatrix);
}

void Collider::updatePhysics()
{
    vec3 linearAcceleration = netForce * computedInverseMass();
    velocity += linearAcceleration * Physics::elapsedStepSeconds;
    transform->position += velocity * Physics::elapsedStepSeconds;

    auto angularAcceleration = transformDirection(netTorque, getInverseWorldInertiaTensor());
    angularVelocity += angularAcceleration * Physics::elapsedStepSeconds;

    float angularSpeed = length(angularVelocity);

    if (angularSpeed > 0)
    {
        auto axis = normalize(angularVelocity);
        auto angle = angularSpeed * Physics::elapsedStepSeconds;
        quat newRotation = angleAxis(angle, axis);
        transform->rotation = newRotation * transform->rotation;
    }
}

void Collider::beforeAttach(GameObject* gameObject)
{
    gameObject->collider = this;
}

void Collider::afterAttach(GameObject* gameObject)
{
    mass = 0.1f;
}

void Collider::updateInetiaTensor()
{
}

bool walt::Collider::isCollided()
{
    return contacts.size() != 0;
}

std::list<glm::vec3> walt::Collider::localContactPoints()
{
    list<vec3> points;

    for (auto contact : contacts)
    {
        if (contact->a == this) {
            points.push_back(contact->localA);
        }
        else if (contact->b == this) {
            points.push_back(contact->localB);
        }
    }

    return points;
}

unsigned int Collider::prevId = -1;
