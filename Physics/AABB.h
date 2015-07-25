#pragma once

#include <list>

#include <stdafx.h>

namespace walt
{
    class Collider;

    class AABB
    {
    public:
        AABB();
        ~AABB();

        static bool FindCollision(Collider& a, Collider& b);

        glm::vec3 position;
        glm::vec3 halfScale;
        glm::vec3 scale;
    };
}
