#pragma once

#include <Physics/Collider.h>

#include <stdafx.h>

namespace walt
{
    class SphereCollider : public Collider
    {
    public:
        SphereCollider();
        ~SphereCollider();

        virtual glm::vec3 findSupport(glm::vec3& direction) override;

        virtual void updateInetiaTensor() override;
    };
}
