#include "GameObject.h"

#include <Component.h>
#include <Components/Transform.h>
#include <PrimitiveGenerator.h>

using namespace walt;

GameObject::GameObject()
{
    transform = new Transform();
    addComponent(transform);
}

GameObject::~GameObject()
{
    for (auto it = components.begin(); it != components.end();)
    {
        delete *it;
        it = components.erase(it);
    }
}

GameObject* GameObject::Instantiate(GameObject* original, glm::vec3& position, glm::quat &rotation)
{
    auto* gameObject = new GameObject(*original);
    gameObject->transform->position = position;
    gameObject->transform->rotation = rotation;

    return gameObject;
}

GameObject* GameObject::CreatePrimitive(PrimitiveType primitiveType)
{
    return PrimitiveGenerator::createPrimitive(primitiveType);
}

void GameObject::addComponent(Component* component)
{
    component->beforeAttach(this);
    component->gameObject = this;
    component->transform = transform;
    components.push_back(component);
    component->afterAttach(this);
}

void GameObject::update()
{
    for (auto* component : components)
    {
        component->update();
    }
}

void GameObject::draw()
{
    for (auto* component : components)
    {
        component->draw();
    }
}
