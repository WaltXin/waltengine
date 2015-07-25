#include "Behavior.h"

#include <GameObject.h>

using namespace walt;

Behavior::Behavior()
{
}

Behavior::~Behavior()
{
}

void Behavior::beforeAttach(GameObject* gameObject)
{
    this->gameObject = gameObject;
    transform = gameObject->transform;
}
