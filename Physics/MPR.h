#pragma once

#include <list>

#include <stdafx.h>

namespace walt
{
    class Collider;

    class MPR
    {
    public:
        MPR();
        ~MPR();

        static bool FindCollision(Collider& a, Collider& b, glm::vec3& worldA, glm::vec3& worldB, glm::vec3& normal);
    };
}
