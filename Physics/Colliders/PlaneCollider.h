#pragma once

#include <Physics/Collider.h>

#include <stdafx.h>

namespace walt
{
    class PlaneCollider : public Collider
    {
    public:
        PlaneCollider();
        ~PlaneCollider();

        virtual glm::vec3 findSupport(glm::vec3& direction) override;

        virtual void updateInetiaTensor() override;
    };
}
