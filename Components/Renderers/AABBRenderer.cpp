#include "AABBRenderer.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include <Components/Camera.h>
#include <Components/MeshFilter.h>
#include <Components/Transform.h>
#include <GameObject.h>
#include <Material.h>
#include <Mesh.h>
#include <Shader.h>

using namespace walt;
using namespace glm;

AABBRenderer::AABBRenderer()
{
    renderType = RenderType::Surface;
    materials.push_back(Material::load(MaterialType::PhongMaterial));
}

AABBRenderer::~AABBRenderer()
{
}

void AABBRenderer::draw()
{
    auto* material = getMaterial();
    auto* shader = material->shader;
    
    auto worldMatrix = transform->getWorldMatrix();
    auto wvp = Camera::current->vpMatrix * worldMatrix;

    material->setWVP(wvp);
    material->setWorldMatrix(worldMatrix);
    material->setCameraPos(Camera::current->transform->position());

    auto* mesh = gameObject->meshFilter->mesh;
    mesh->bind();

    glDrawElements(
        getRenderMode(),
        mesh->numTriangles * 3,
        GL_UNSIGNED_INT,
        0);
}

GLenum walt::AABBRenderer::getRenderMode()
{
    switch (renderType)
    {
    case walt::AABBRenderer::RenderType::WireFrame:
        return GL_LINE_STRIP;
    case walt::AABBRenderer::RenderType::Surface:
    default:
        return GL_TRIANGLES;
    }
}
