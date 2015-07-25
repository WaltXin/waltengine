#include "GameObjectManager.h"

#include <Components/Transform.h>
#include <GameObject.h>

using namespace walt;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::destroy()
{
    auto& objects = Transform::roots;

    for (auto it = objects.begin(); it != objects.end();)
    {
        delete *(it++);
    }
}

void GameObjectManager::update()
{
    for (auto& transform : Transform::roots)
    {
        transform->gameObject->update();
    }
}

void GameObjectManager::draw()
{
    for (auto& transform : Transform::roots)
    {
        transform->gameObject->draw();
    }
}
