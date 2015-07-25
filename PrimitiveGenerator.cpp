#include "PrimitiveGenerator.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <Physics/Colliders/BoxCollider.h>
#include <Physics/Colliders/PlaneCollider.h>
#include <Physics/Colliders/SphereCollider.h>
#include <Components/Renderers/MeshRenderer.h>
#include <Components/MeshFilter.h>
#include <GameObject.h>
#include <Material.h>
#include <Mesh.h>
#include <Resources.h>
#include <Shader.h>

using namespace walt;
using namespace glm;

PrimitiveGenerator::PrimitiveGenerator()
{
}

PrimitiveGenerator::~PrimitiveGenerator()
{
}

GameObject* PrimitiveGenerator::createPrimitive(PrimitiveType primitiveType)
{
    GameObject* gameObject = nullptr;

    switch (primitiveType)
    {
    case PrimitiveType::Cube:
        gameObject = Resources::load("Assets/Models/Cube.dae");
        break;
    case PrimitiveType::Sphere:
    default:
        gameObject = Resources::load("Assets/Models/Sphere.dae");
        break;
    }

    return gameObject;
}

Collider* walt::PrimitiveGenerator::createCollider(PrimitiveType primitiveType)
{
    switch (primitiveType)
    {
    case PrimitiveType::Cube:
        return new BoxCollider();
    case PrimitiveType::Sphere:
        return new SphereCollider();
    case PrimitiveType::Plane:
        return new PlaneCollider();
    default:
        return nullptr;
    }
}
