#pragma once

#include <Component.h>

#include <list>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <stdafx.h>

namespace walt
{
    class GameObject;

    class Transform : public Component
    {
    public:
        Transform();
        ~Transform();

        virtual void beforeAttach(GameObject* gameObject) override;

        virtual void update() override;
        virtual void draw() override;

        Transform* getParent();
        void setParent(Transform* value);

        void clearChildren();

        //TODO: don't rely on compiler return-value optimization
        glm::mat4 getWorldMatrix();
        glm::mat4 getInverseWorldMatrix();
        glm::vec3 toWorldPosition(glm::vec3& v);
        glm::vec3 toWorldDirection(glm::vec3& v);
        glm::vec3 toLocalPosition(glm::vec3& v);
        glm::vec3 toLocalDirection(glm::vec3& v);

        void lookAt(glm::vec3& target);

        float getHalfWidth();
        float getHalfHeight();
        float getHalfDepth();

        //TODO: implement C++ property
        obj_attr<glm::vec3> position;

        glm::quat rotation;
        glm::vec3 scaling;

        static std::list<Transform*> roots;

    protected:
        Transform* parent;
        std::list<Transform*> children;
    };
}
