#include "SphereCollider.h"

#include <glm/gtx/transform.hpp>

#include <Components/Transform.h>

using namespace walt;
using namespace glm;

SphereCollider::SphereCollider()
    : Collider()
{
}

SphereCollider::~SphereCollider()
{
}

vec3 SphereCollider::findSupport(vec3& direction)
{
    vec3 localDirection = transform->toLocalDirection(direction);
    localDirection *= 0.5f / length(localDirection);

    return transform->toWorldPosition(localDirection);
}

void SphereCollider::updateInetiaTensor()
{
    if (inverseMass != 0)
    {
        auto wSqr = transform->scaling.x * transform->scaling.x;
        auto hSqr = transform->scaling.y * transform->scaling.y;
        auto dSqr = transform->scaling.z * transform->scaling.z;
        auto c = mass / 5;

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
