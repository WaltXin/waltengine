#pragma once

#include <list>

#include <stdafx.h>

namespace walt
{
    class Collider;
    class Contact;
    class SolverManager;

    class Solver
    {
    public:
        Solver(SolverManager* manager, Collider* a, Collider* b);
        ~Solver();

        void update();

        void addContact(glm::vec3& worldA, glm::vec3& worldB, glm::vec3& normal);

        Collider* a;
        Collider* b;
        std::list<Contact*> contacts;
        SolverManager* manager;
    };
}
