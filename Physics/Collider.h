#pragma once

#include <glm/glm.hpp>

#include <Component.h>

#include <stdafx.h>

namespace walt
{
    class AABB;
    class Contact;
    class Solver;

    class Collider : public Component
    {
    public:
        Collider();
        ~Collider();

        virtual void beforeAttach(GameObject* gameObject) override;
        virtual void afterAttach(GameObject* gameObject) override;

        virtual void updatePhysics();
        virtual glm::vec3 findSupport(glm::vec3& normal) = 0;

        bool isCollided();
        std::list<glm::vec3> localContactPoints();
        std::list<Contact*> contacts;
        std::list<Solver*> solvers;

        glm::mat4 getInertiaTensor();
        void setInertiaTensor(glm::mat4& value);
        glm::mat4 getInverseWorldInertiaTensor();

        value_attr<float> inverseMass;
        value_attr<float> mass;
        value_attr<bool> dynamic;
        value_attr<bool> kinematic;
        value_attr<float> computedInverseMass;

        glm::mat4 inverseInertiaTensor;

        glm::vec3 velocity;
        glm::vec3 angularVelocity;

        glm::vec3 netForce;
        glm::vec3 netTorque;

        glm::vec3 prevPos;
        glm::quat prevRotation;

        AABB* aabb;

        //TODO: modify this naive hash func
        static const unsigned int MaxId = 65535;
        static unsigned int prevId;
        unsigned int id;

    protected:
        virtual void updateInetiaTensor();

        float _inverseMass;
    };
}
