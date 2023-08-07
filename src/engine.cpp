#include<core/engine.hpp>
#include<iostream>
#include<SDL.h>
#include<log.hpp>

namespace game{

    bool Engine::Initialize(){

        bool ret{true};
        mLogManager.Initialize();
        GetInfo();

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
            LOG_ERROR("Failed to Initialize SDL: {}\n", SDL_GetError());
            ret = false;
        } else {
            SDL_version version;
            SDL_VERSION(&version);
            LOG_TRACE("SDL v{}.{}.{}", version.major, version.minor, version.patch);
        }

        return ret;
    }

    void Engine::Shutdown(){
        
        mLogManager.Shutdown();
        SDL_Quit();
    }

    void Engine::GetInfo(){

    LOG_TRACE("Game v{}.{}", GAME_MAJOR_VERSION, GAME_MINOR_VERSION);
#ifdef GAME_DEBUG
    // std::cout << "Configuration: DEBUG\n";
    LOG_DEBUG("Configuration: DEBUG");
#elif GAME_RELEASE
    // std::cout << "Configuration: RELEASE\n";
#endif
    }

    //Singleton

    Engine* Engine::instance = nullptr;

    Engine::Engine(){}

    Engine& Engine::GetInstance(){
        if (instance == nullptr)
            instance = new Engine();

        return *instance;
    }

}