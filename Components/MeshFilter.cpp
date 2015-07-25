#include "MeshFilter.h"

#include <GameObject.h>

#include <Mesh.h>

using namespace walt;

MeshFilter::MeshFilter()
{
}

MeshFilter::~MeshFilter()
{
    delete mesh;
}

void MeshFilter::beforeAttach(GameObject* gameObject)
{
    gameObject->meshFilter = this;
}
