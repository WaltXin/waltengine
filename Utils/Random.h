#pragma once

#include <glm/glm.hpp>

namespace walt
{
    class Random
    {
    public:
        static float randFloat();
        static glm::vec3 randVec3();

    private:
        Random();
        ~Random();
        static Random intance;
    };
}
