#pragma once

#include <list>

#include <stdafx.h>

namespace walt
{
    class Collider;
    class ContactConstraint;

    class Contact
    {
    public:
        Contact(Collider* a, Collider* b, glm::vec3& worldA, glm::vec3& worldB, glm::vec3& normal);
        ~Contact();

        Collider* a;
        Collider* b;

        glm::vec3 localA;
        glm::vec3 localB;
        glm::vec3 point;
        glm::vec3 normal;
        long long totalTicks;
        ContactConstraint* constraint;

        void update(glm::vec3& worldA, glm::vec3& worldB, glm::vec3& normal);

        float getDistance();
        float getDistanceSquared();
    };
}
