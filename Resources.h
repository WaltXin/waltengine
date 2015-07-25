#pragma once

#include <stdafx.h>

namespace Assimp
{
    class Importer;
}

namespace walt
{
    class GameObject;

    class Resources
    {
    public:
        Resources();
        ~Resources();

        static GameObject* load(const char* path);

        static Resources *instance;
    };
}
