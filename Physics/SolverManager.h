#pragma once

#include <list>
#include <unordered_map>
#include <utility>
#include <stdafx.h>

namespace walt
{
    class Collider;
    class Solver;

    class SolverManager
    {
    public:
        SolverManager();
        ~SolverManager();

        void update();
        Solver* getSolver(Collider* a);
        Solver* getSolver(Collider* a, Collider* b);
        void addContact(Collider* a, Collider* b, glm::vec3& worldA, glm::vec3& worldB, glm::vec3& normal);

        int iteration;

        std::unordered_map<unsigned int, Solver*> solvers;
    };
}
