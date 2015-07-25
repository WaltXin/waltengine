#include "Component.h"

#include <GameObject.h>

using namespace walt;

Component::Component()
    : Object()
{
}

Component::~Component()
{
}

void Component::beforeAttach(GameObject* gameObject)
{
}

void Component::afterAttach(GameObject* gameObject)
{

}
