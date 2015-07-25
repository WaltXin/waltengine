#pragma once

#include <Object.h>

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <stdafx.h>
#include <PrimitiveType.h>

namespace walt
{
    class Collider;
    class Component;
    class MeshFilter;
    class MeshRenderer;
    class Renderer;
    class Transform;

    class GameObject : public Object
    {
    public:
        GameObject();
        ~GameObject();

        static GameObject* Instantiate(GameObject* original, glm::vec3& position, glm::quat &rotation);
        static GameObject* CreatePrimitive(PrimitiveType primitiveType);

        void addComponent(Component* component);

        virtual void update() override;
        virtual void draw() override;

        //TODO: use reflection to implement FindObjectOfType
        //TODO: implement properties
        MeshFilter* meshFilter;
        Renderer* renderer;
        Transform* transform;
        Collider* collider;

        std::list<Renderer*> renderers;

    protected:
        std::vector<Component*> components;
    };
}
