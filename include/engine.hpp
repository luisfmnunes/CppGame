#pragma once

#include <log.hpp>
#include <core/window.hpp>
#include <manager/logManager.hpp>

namespace game{

    class Engine{

    public:
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        static Engine& GetInstance();
        ~Engine() {}

        void Run();
        inline void Quit() { mIsRunning = false; }
        

    private:
        bool mIsRunning;
        core::Window mWindow;
        //Managers
        managers::LogManager mLogManager;
        [[nodiscard]] bool Initialize();
        void Shutdown();
        static Engine* instance;

    protected:
        Engine();
        void GetInfo();


    };

}