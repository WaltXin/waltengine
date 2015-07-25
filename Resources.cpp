#include "Resources.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <Physics/Colliders/BoxCollider.h>
#include <Components/Renderers/MeshRenderer.h>
#include <Components/MeshFilter.h>
#include <GameObject.h>
#include <Mesh.h>
#include <Material.h>
#include <Shader.h>

using namespace walt;
using namespace glm;
using namespace Assimp;
using namespace std;

Resources::Resources()
{
}

Resources::~Resources()
{
}

GameObject* Resources::load(const char* path)
{
    Importer importer;

    auto* scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (!scene) {
        fprintf(stderr, "Error: '%s'\n", importer.GetErrorString());
        throw 1;
    }

    auto* aimesh = scene->mMeshes[0];
    assert(aimesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);

    auto* vertices = new vec3[aimesh->mNumVertices];
    auto* normals = new vec3[aimesh->mNumVertices];
    auto* triangles = new uvec3[aimesh->mNumVertices];

    for (unsigned int i = 0; i < aimesh->mNumVertices; i++)
    {
        auto vertex = toGlmVec3(aimesh->mVertices[i]);
        vertices[i] = vertex;

        auto normal = toGlmVec3(aimesh->mNormals[i]);
        normals[i] = normal;
    }

    for (unsigned int i = 0; i < aimesh->mNumFaces; i++)
    {
        auto& face = aimesh->mFaces[i];
        triangles[i] = uvec3(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
    }

    auto* mesh = new Mesh();
    mesh->setVertices(vertices, aimesh->mNumVertices);
    mesh->setNormals(normals, aimesh->mNumVertices);
    mesh->setTriangles(triangles, aimesh->mNumFaces);

    auto* gameObject = new GameObject();

    auto* meshFilter = new MeshFilter();
    meshFilter->mesh = mesh;
    gameObject->addComponent(meshFilter);

    auto* renderer = new MeshRenderer();
    gameObject->addComponent(renderer);

    return gameObject;
}

Resources * Resources::instance;
