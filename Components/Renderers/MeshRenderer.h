#pragma once

#include <Components/Renderer.h>

#include <stdafx.h>

namespace walt
{
    enum class RenderType
    {
        Surface,
        WireFrame
    };

    class MeshRenderer : public Renderer
    {
    public:
        MeshRenderer();
        ~MeshRenderer();

        virtual void draw() override;

        RenderType renderType;

        unsigned int getRenderMode();
    };
}
