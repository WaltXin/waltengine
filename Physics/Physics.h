#pragma once

#include <list>

#include <stdafx.h>

namespace walt
{
    class Collider;
    class SolverManager;

    class Physics
    {
    public:
        Physics();
        ~Physics();

        static void update();

        static void add(Collider* collider);
        static void remove(Collider* collider);

        static Physics instance;

        static glm::vec3 gravity;
        static float friction;
        static int numSteps;
        static int numSolverIteration;
        static float effectiveMassFactor;
        static float betaFactor;
        static float positionErrorDiminish;

        static float elapsedStepSeconds;
        static long long elapsedStepTicks;
        static float totalSeconds;
        static long long totalTicks;
        static float timeRatio;

    protected:
        void updateAll();

        std::list<Collider*> colliders;
        SolverManager* solverManager;
    };
}
