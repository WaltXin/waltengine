#pragma once

#include <Components/Renderer.h>

#include <stdafx.h>

namespace walt
{
    class AABBRenderer : public Renderer
    {
    public:
        enum class RenderType
        {
            Surface,
            WireFrame
        };

        AABBRenderer();
        ~AABBRenderer();

        virtual void draw() override;

        RenderType renderType;

        unsigned int getRenderMode();
    };
}
