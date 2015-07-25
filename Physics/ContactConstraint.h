#pragma once

#include <list>

#include <stdafx.h>

namespace walt
{
    class Collider;

    class ContactConstraint
    {
    public:
        ContactConstraint(Collider* a, Collider* b, glm::vec3& localA, glm::vec3& localB, glm::vec3& normal);
        ~ContactConstraint();

        Collider* a;
        Collider* b;
        glm::vec3 localA;
        glm::vec3 localB;
        glm::vec3 normal;
        float positionError;
        glm::vec3 invMomentA;
        glm::vec3 invMomentB;
        float effectiveMass;
        float beta;
        float cachedMomentum;
        glm::vec3 cachedAngularMomentum;

        void prepareForIteration();
        void iterate();
        void update(glm::vec3& localA, glm::vec3& localB, glm::vec3& normal);
    };
}
