#pragma once

#include <PrimitiveType.h>
#include <stdafx.h>

namespace walt
{
    class Collider;
    class GameObject;

    class PrimitiveGenerator
    {
    public:
        PrimitiveGenerator();
        ~PrimitiveGenerator();

        static GameObject* createPrimitive(PrimitiveType primitiveType);
        static Collider* createCollider(PrimitiveType primitiveType);

    protected:
        static GameObject* createCube();
        static GameObject* createSphere(int numSlices = 30);
    };
}
