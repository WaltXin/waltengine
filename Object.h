#pragma once

#include <stdafx.h>

namespace walt
{
    class Object
    {
    public:
        Object();
        ~Object();

        virtual void update();
        virtual void draw();

    protected:
    };
}
