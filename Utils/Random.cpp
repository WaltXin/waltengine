#include "Random.h"

#include <ctime>
#include <random>

using namespace walt;
using namespace glm;

Random::Random()
{
    srand((unsigned int)time(NULL));
}

Random::~Random()
{
}

float walt::Random::randFloat()
{
    return fmod(rand(), 100.f) / 100.f;
}

glm::vec3 walt::Random::randVec3()
{
    return vec3(randFloat(), randFloat(), randFloat());
}

walt::Random walt::Random::intance;
