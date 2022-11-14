#ifndef H_CORE
#define H_CORE



#include <iostream>

namespace Core {

/**
 * Initializing game components so game can start running.
 * 
 * Must be called before any other calls.
 */
void initializate();


/**
 * Starts main cycle of the game.
 */
void run();


/**
 * Checks if the game must be shut down due to window close
 * signal, UI exit button or etc.
 * 
 * @return true If something send signal to close game.
 */
bool isGameEnterupted();


} // namespace Game

#endif