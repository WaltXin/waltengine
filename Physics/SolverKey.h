#pragma once

#include <stdafx.h>

namespace walt
{
    class Collider;

    class SolverKey
    {
    public:
        static unsigned int get(Collider* a, Collider* b);
    };
}
