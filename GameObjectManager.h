#pragma once

#include <stdafx.h>

namespace walt
{
    class GameObjectManager
    {
    public:
        GameObjectManager();
        ~GameObjectManager();

        static void destroy();
        static void update();
        static void draw();
    };
}
