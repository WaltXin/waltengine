#include "WaltEngine.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>

#include <Physics/Physics.h>
#include <GameObjectManager.h>
#include <Input.h>

using namespace walt;

WaltEngine::WaltEngine(int* argc, char** argv)
{
    //TODO: throw exception
    if (instance != nullptr) throw 1;
    instance = this;

    instance->initOpenGL(argc, argv);
    instance->initObjects();
}

WaltEngine::~WaltEngine()
{
    GameObjectManager::destroy();

    if (instance != nullptr) instance = nullptr;
}

void WaltEngine::run()
{
    // Begin infinite event loop
    glutMainLoop();

    delete instance;
}

void WaltEngine::initOpenGL(int* argc, char** argv)
{
    // Set up the window
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitWindowSize(width, height);
    glutCreateWindow("Game");

    // Tell glut where the display function is
    glutDisplayFunc(loop);
    glutIdleFunc(loop);

    // A call to glewInit() must be done after glut is initialized!
    GLenum res = glewInit();

    // Check for any errors
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        throw 1;
    }

    glEnable(GL_DEPTH_TEST);

    wglSwapIntervalEXT(1);
}

void WaltEngine::initObjects()
{
    Input::init();

    previousTotalSeconds = 0;
}

void WaltEngine::loop()
{
    instance->update();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    instance->draw();

    glutSwapBuffers();
}

void WaltEngine::update()
{
    updateTime();

    Input::update();
    GameObjectManager::update();

    if (running) {
        Physics::update();
    }

    // exit game if press esc
    if (Input::curr.keyDown[27]) glutLeaveMainLoop();
}

void WaltEngine::updateTime()
{
    float newTotalSeconds = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    if (nextRunning)
    {
        prevElapsedSeconds = elapsedSeconds;
        elapsedSeconds = newTotalSeconds - previousTotalSeconds;
        totalSeconds += elapsedSeconds;
        elapsedTicks = (long long)(elapsedSeconds * 1e7);
        totalTicks = elapsedTicks;
        timeRatio = prevElapsedSeconds == 0 ? 0 : elapsedSeconds / prevElapsedSeconds;
    }
    else
    {
        elapsedSeconds = 0;
        elapsedTicks = 0;
        timeRatio = 0;
    }

    running = nextRunning;
    previousTotalSeconds = newTotalSeconds;
}

void WaltEngine::draw()
{
    GameObjectManager::draw();
}

bool walt::WaltEngine::getRunning()
{
    return running;
}

WaltEngine* WaltEngine::instance;
int WaltEngine::width = 1024;
int WaltEngine::height = 768;
float WaltEngine::elapsedSeconds = 0;
float WaltEngine::totalSeconds = 0;
bool walt::WaltEngine::nextRunning = true;
bool WaltEngine::running = true;
long long WaltEngine::elapsedTicks;
long long WaltEngine::totalTicks;
float WaltEngine::timeRatio;
float WaltEngine::prevElapsedSeconds;
