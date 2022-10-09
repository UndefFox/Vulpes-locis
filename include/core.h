#ifndef H_CORE
#define H_CORE



#include <iostream>

namespace Game {

/**
 * Singleton class of the core of the game. Control how game is running.
 */
class Core {
public:

private:



public:
    /**
     * @brief Get the instance of core 
     * 
     * @return Core& instance of class
     */
    static Core& getInstance();

private:
    Core(){};


public:
    /**
     * Initializing game components so game can start running.
     * 
     * Must be called before any other calls.
     */
    void initializate();

public:
    /**
     * Stops all procces to shut the game.
     * 
     * Needed to call after ending game cycle.
     */
    void terminate();

public:
    /**
     * Starts main cycle of the game.
     */
    void run();

public:
    /**
     * Checks if the game must be shut down due to window close
     * signal, UI exit button or etc.
     * 
     * @return true If something send signal to close game.
     */
    bool isGameEnterupted();
};


} // namespace Game

#endif