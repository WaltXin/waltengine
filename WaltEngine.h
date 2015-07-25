#pragma once

#include <stdafx.h>

namespace walt
{
    // static
    class WaltEngine
    {
    public:
        WaltEngine(int* argc, char** argv);
        ~WaltEngine();

        static void run();
        static bool getRunning();

        static WaltEngine* instance;

        static int width;
        static int height;

        static bool nextRunning;
        static float elapsedSeconds;
        static float totalSeconds;
        static long long elapsedTicks;
        static long long totalTicks;
        static float timeRatio;
        static float prevElapsedSeconds;

    protected:
        void initOpenGL(int* argc, char** argv);
        void initObjects();
        static void loop();

        void update();
        void updateTime();

        void draw();

        static bool running;
        float previousTotalSeconds;
    };
}
