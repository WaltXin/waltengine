#include "Renderer.h"

#include <GameObject.h>

using namespace walt;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::beforeAttach(GameObject* gameObject)
{
    if (gameObject->renderers.size() == 0) {
        gameObject->renderer = this;
    }

    gameObject->renderers.push_back(this);
}
