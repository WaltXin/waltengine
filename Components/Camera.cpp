#include "Camera.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include <Components/Transform.h>
#include <GameObject.h>
#include <WaltEngine.h>

using namespace walt;
using namespace glm;

Camera::Camera()
{
    current = this;
    glutReshapeFunc(onWindowSizeChanged);
}

Camera::~Camera()
{
}

void Camera::onWindowSizeChanged(int w, int h)
{
    if (h == 0) h = 1;

    WaltEngine::width = w;
    WaltEngine::height = h;

    glViewport(0, 0, w, h);

    current->aspect = (float)w / h;

    current->projectionMatrix = perspective(current->fieldOfView, current->aspect, current->nearClipPlane, current->farClipPlane);
}

void Camera::draw()
{
    worldToCameraMatrix = lookAt(transform->position(), targetPos, vec3(0, 1, 0));
    vpMatrix = projectionMatrix * worldToCameraMatrix;
}

void Camera::setBackgroundColor(vec4& value)
{
    glClearColor(value.x, value.y, value.z, value.w);
}

Camera* Camera::current;
