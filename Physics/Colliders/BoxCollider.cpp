#include "BoxCollider.h"

#include <glm/gtx/transform.hpp>

#include <Components/Transform.h>

using namespace walt;
using namespace glm;

BoxCollider::BoxCollider()
    : Collider()
{
}

BoxCollider::~BoxCollider()
{
}

vec3 BoxCollider::findSupport(vec3& direction)
{
    vec3 localDirection = transform->toLocalDirection(direction);

    auto x = normalize(localDirection.x) * 0.5f;
    auto y = normalize(localDirection.y) * 0.5f;
    auto z = normalize(localDirection.z) * 0.5f;
    auto localSupport = vec3(x, y, z);
    return transform->toWorldPosition(localSupport);
}

void BoxCollider::updateInetiaTensor()
{
    if (inverseMass != 0)
    {
        auto wSqr = transform->scaling.x * transform->scaling.x;
        auto hSqr = transform->scaling.y * transform->scaling.y;
        auto dSqr = transform->scaling.z * transform->scaling.z;
        auto c = mass / 12;

        mat4 inertiaTensor(
            c * (hSqr + dSqr), 0, 0, 0,
            0, c * (wSqr + dSqr), 0, 0,
            0, 0, c * (wSqr * hSqr), 0,
            0, 0, 0, 1);

        setInertiaTensor(inertiaTensor);
    }
    else
    {
        inverseInertiaTensor = mat4(0);
    }
}
