#include "Contact.h"

#include <glm/gtx/norm.hpp>

#include <Components/Transform.h>
#include <Physics/Collider.h>
#include <Physics/ContactConstraint.h>
#include <Physics/Physics.h>
#include <GameObject.h>

using namespace walt;
using namespace glm;

Contact::Contact(Collider* a, Collider* b, glm::vec3& worldA, glm::vec3& worldB, glm::vec3& normal)
{
    this->a = a;
    this->b = b;
    localA = a->transform->toLocalPosition(worldA);
    localB = b->transform->toLocalPosition(worldB);
    point = 0.5f * (worldA + worldB);
    this->normal = normal;
    constraint = new ContactConstraint(a, b, localA, localB, normal);
    totalTicks = Physics::totalTicks;
}

Contact::~Contact()
{
    delete constraint;
}

float Contact::getDistance()
{
    vec3 worldA = a->transform->toWorldPosition(localA);
    vec3 worldB = b->transform->toWorldPosition(localB);
    return length(worldB - worldA);
}

float Contact::getDistanceSquared()
{
    vec3 worldA = a->transform->toWorldPosition(localA);
    vec3 worldB = b->transform->toWorldPosition(localB);
    return length2(worldB - worldA);
}

void Contact::update(glm::vec3& worldA, glm::vec3& worldB, glm::vec3& normal)
{
    localA = a->transform->toLocalPosition(worldA);
    localB = b->transform->toLocalPosition(worldB);
    point = 0.5f * (worldA + worldB);
    this->normal = normal;
    totalTicks = Physics::totalTicks;
    constraint->update(localA, localB, normal);
}
