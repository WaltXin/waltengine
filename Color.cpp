#include "Color.h"

using namespace walt;
using namespace glm;

Color::Color()
{
}

Color::Color(int r, int g, int b)
    : Color(r, g, b, 255)
{
}

Color::Color(int r, int g, int b, int a)
    : vec4(r / 256.f, g / 256.f, b / 256.f, a / 256.f)
{
}

Color::Color(float r, float g, float b)
    : Color(r, g, b, 1.f)
{
}

Color::Color(float r, float g, float b, float a)
    : vec4(r, g, b, a)
{

}

walt::Color::Color(const Color& rgb, float a)
    : vec4(rgb.r, rgb.g, rgb.b, a)
{

}

Color::~Color()
{
}

const Color Color::Red(1.f, 0.f, 0.f, 1.f);
const Color Color::Green(0.f, 1.f, 0.f, 1.f);
const Color Color::Blue(0.f, 0.f, 1.f, 1.f);
const Color Color::White(1.f, 1.f, 1.f, 1.f);
const Color Color::Black(0.f, 0.f, 0.f, 1.f);
const Color Color::Gray(.5f, .5f, .5f, 1.f);
const Color walt::Color::WaterBlue(153, 217, 234);
