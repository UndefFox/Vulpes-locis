#ifndef H_CORE
#define H_CORE

#include "graphics/renderengine.h"

#include <iostream>

namespace Game {

/**
 * Singleton class of the core of the game. Control how game is running.
 */
class Core {
public:

private:
    


public:
    static Core& getInstance();

private:
    Core() { };


public:
    /**
     * Initializing game components so game can start running.
     */
    void initializate();

public:
    /**
     * Stops all procces to shut the game.
     */
    void terminate();

public:
    void run();
};


} // namespace Game

#endif