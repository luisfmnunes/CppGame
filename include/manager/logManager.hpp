#pragma once

namespace game::managers{

    class LogManager{

    public:

        LogManager() = default;
        ~LogManager() = default;

        void Initialize();
        void Shutdown();

    };

}