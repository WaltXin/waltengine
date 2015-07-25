#pragma once

#include <Object.h>

#include <glm/glm.hpp>

#include <stdafx.h>

namespace walt
{
    class Color : public glm::vec4
    {
    public:
        Color();
        Color(int r, int g, int b);
        Color(int r, int g, int b, int a);
        Color(float r, float g, float b);
        Color(float r, float g, float b, float a);
        Color(const Color& rgb, float a);
        ~Color();

        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color White;
        static const Color Black;
        static const Color Gray;
        static const Color WaterBlue;
    };
}
