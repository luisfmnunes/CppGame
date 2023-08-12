#include<engine.hpp>
#include<iostream>
#include<SDL.h>
#include<log.hpp>

namespace game{

    void Engine::Run(){
        LOG_ASSERT(Initialize(), "Couldn't Initialize Game Engine. Shutting Down");

        while(mIsRunning){
            mWindow.PumpEvents();

            mWindow.BeginRender();
            mWindow.EndRender();
        }

    }

    bool Engine::Initialize(){

        bool ret{false};
        mLogManager.Initialize();
        GetInfo();

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
            LOG_ERROR("Failed to Initialize SDL: {}\n", SDL_GetError());
        } else {
            SDL_version version;
            SDL_VERSION(&version);
            LOG_TRACE("SDL v{}.{}.{}", version.major, version.minor, version.patch);

            if(mWindow.Create()){
                ret = true;
                mIsRunning = true;
            }
        }

        if(!ret)
            Shutdown();

        return ret;
    }

    void Engine::Shutdown(){
        
        mLogManager.Shutdown();
        mWindow.Shutdown();
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

    Engine::Engine() : mIsRunning(false) {}

    Engine& Engine::GetInstance(){
        if (!instance)
            instance = new Engine();

        return *instance;
    }

}