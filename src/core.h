#ifndef H_CORE
#define H_CORE

/**
 * Core of the game that controll its execution.
 */
namespace Core {

/**
 * Executing all functions that need to be run once on the game start.
 */
void initializate();

/**
 * Sets all values to set game into state of game start.
 */
void setupInitialState();

/**
 * Starts main cycle of the game.
 */
void run();

/**
 * Returning all systems to initial state.
 */
void cleanup();

/**
 * Executing all functions that need to run once on the game termination.
 */
void terminate();



} // namespace Game

#endif