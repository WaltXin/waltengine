#pragma once

#include <Component.h>

#include <stdafx.h>

namespace walt
{
    class GameObject;
    class Transform;

    class Behavior : public Component
    {
    public:
        Behavior();
        ~Behavior();

        virtual void beforeAttach(GameObject* gameObject) override;

        GameObject* gameObject;
        Transform* transform;
    };
}
