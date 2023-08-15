#pragma once

#include <log.hpp>
#include <core/window.hpp>
#include <manager/logManager.hpp>
#include <manager/renderManager.hpp>

namespace game{

    class Engine{

    public:
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        static Engine& GetInstance();
        ~Engine() {}

        void Run();
        inline void Quit() { mIsRunning = false; }
        
        //Managers
        inline managers::RenderManager& GetRenderManager() { return mRenderManager; }

    private:
        bool mIsRunning;
        bool mIsInitialized;
        core::Window mWindow;
        
        //Managers
        managers::LogManager mLogManager;
        managers::RenderManager mRenderManager;

        [[nodiscard]] bool Initialize();
        void Shutdown();
        static Engine* instance;

    protected:
        Engine();
        void GetInfo();


    };

}