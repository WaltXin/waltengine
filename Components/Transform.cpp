#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <GameObject.h>

using namespace walt;
using namespace glm;
using namespace std;

Transform::Transform()
    : scaling(1, 1, 1)
{
    roots.push_back(this);
}

Transform::~Transform()
{
    clearChildren();

    auto& siblings = parent == nullptr ? roots : parent->children;

    for (auto it = siblings.begin(); it != siblings.end();)
    {
        if (*it == this) {
            it = siblings.erase(it);
            break;
        }
        else {
            ++it;
        }
    }
}

Transform* Transform::getParent()
{
    return parent;
}

void Transform::setParent(Transform* value)
{
    auto& siblings = parent == nullptr ? roots : parent->children;

    for (auto it = siblings.begin(); it != siblings.end();)
    {
        if (*it == this) {
            it = siblings.erase(it);
            break;
        }
        else {
            ++it;
        }
    }

    auto& newSiblings = value == nullptr ? roots : value->children;
    newSiblings.push_back(this);

    parent = value;
}

void walt::Transform::clearChildren()
{
    for (auto it = children.begin(); it != children.end();)
    {
        delete *(it++);
    }
}

mat4 Transform::getWorldMatrix()
{
    if (parent != nullptr) {
        auto parentWorldMatrix = parent->getWorldMatrix();
        auto translateMatrix = translate(position());
        auto rotationMatrix = toMat4(rotation);
        auto scalingMatrix = scale(this->scaling);
        return parentWorldMatrix * translateMatrix * rotationMatrix * scalingMatrix;
    }
    else {
        auto translateMatrix = translate(position());
        auto rotationMatrix = toMat4(rotation);
        auto scalingMatrix = scale(this->scaling);
        return translateMatrix * rotationMatrix * scalingMatrix;
    }
}

mat4 Transform::getInverseWorldMatrix()
{
    return inverse(getWorldMatrix());
}

vec3 Transform::toWorldPosition(vec3& v)
{
    return transformPosition(v, getWorldMatrix());
}

vec3 Transform::toWorldDirection(vec3& v)
{
    auto worldMatrix = getWorldMatrix();
    return transformDirection(v, worldMatrix);
}

vec3 Transform::toLocalPosition(vec3& v)
{
    return transformPosition(v, getInverseWorldMatrix());
}

vec3 Transform::toLocalDirection(vec3& v)
{
    return transformDirection(v, getInverseWorldMatrix());
}

float Transform::getHalfWidth()
{
    return scaling.x / 2;
}

float Transform::getHalfHeight()
{
    return scaling.y / 2;
}

float Transform::getHalfDepth()
{
    return scaling.z / 2;
}

void Transform::update()
{
    for (auto* child : children)
    {
        child->gameObject->update();
    }
}

void Transform::draw()
{
    for (auto* child : children)
    {
        child->gameObject->draw();
    }
}

void Transform::lookAt(vec3& target)
{
    throw 1;
}

void Transform::beforeAttach(GameObject* gameObject)
{
    gameObject->transform = this;
}

std::list<Transform*> Transform::roots;
