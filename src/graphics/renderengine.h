#include "graphics/renderengineconfiguration.h"


namespace Game {

/**
 * Singleton class of main render engine of the game.
 */
class RenderEngine {
public:
    RenderEngineConfiguration config;

private:
    


public:
    static RenderEngine& getInstance();

private:
    RenderEngine() {};

public:
    /**
     * Initial intilization to prepare engine to work.
     */
    void initializate();

public:
    /**
     * Terminates all process to stop engine.
     */
    void terminate();

};

} // namespace Game