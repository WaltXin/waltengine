#pragma once

#include <Component.h>

#include <glm/glm.hpp>

#include <stdafx.h>

namespace walt
{
    class Camera : public Component
    {
    public:
        Camera();
        ~Camera();

        static void onWindowSizeChanged(int w, int h);

        virtual void draw() override;
        void setBackgroundColor(glm::vec4& value);

        static Camera* current;

        glm::vec3 targetPos;

        float fieldOfView;
        float aspect;
        float nearClipPlane;
        float farClipPlane;

        glm::mat4 worldToCameraMatrix;
        glm::mat4 projectionMatrix;
        glm::mat4 vpMatrix;
    };
}
