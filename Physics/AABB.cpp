#include "AABB.h"

#include <Components/Transform.h>
#include <Physics/Collider.h>
#include <GameObject.h>

using namespace walt;
using namespace glm;

AABB::AABB()
{
}

AABB::~AABB()
{
}

bool AABB::FindCollision(Collider& colliderA, Collider& colliderB)
{
    auto a = colliderA.transform;
    auto b = colliderB.transform;

    if (a->position().x < b->position().x)
    {
        if (a->position().x + a->getHalfWidth() < b->position().x - b->getHalfWidth()) return false;
    }
    else
    {
        if (b->position().x + b->getHalfWidth() < a->position().x - a->getHalfWidth()) return false;
    }

    if (a->position().y < b->position().y)
    {
        if (a->position().y + a->getHalfHeight() < b->position().y - b->getHalfHeight()) return false;
    }
    else
    {
        if (b->position().y + b->getHalfHeight() < a->position().y - a->getHalfHeight()) return false;
    }

    if (a->position().z < b->position().z)
    {
        if (a->position().z + a->getHalfDepth() < b->position().z - b->getHalfDepth()) return false;
    }
    else
    {
        if (b->position().z + b->getHalfDepth() < a->position().z - a->getHalfDepth()) return false;
    }

    return true;
}
