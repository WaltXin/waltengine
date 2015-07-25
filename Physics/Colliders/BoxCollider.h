#pragma once

#include <Physics/Collider.h>

#include <stdafx.h>

namespace walt
{
    class BoxCollider : public Collider
    {
    public:
        BoxCollider();
        ~BoxCollider();

        virtual glm::vec3 findSupport(glm::vec3& direction) override;

        virtual void updateInetiaTensor() override;
    };
}
