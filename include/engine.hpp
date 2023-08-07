#pragma once

#include <manager/logManager.hpp>

namespace game{

    class Engine{

    public:
        Engine operator=(const Engine&) = delete;

        static Engine& GetInstance();

        void Run();
        bool Initialize();
        void Shutdown();

    private:
        
        //Managers
        managers::LogManager mLogManager;

    protected:
        Engine();
        static Engine* instance;
        void GetInfo();


    };

}