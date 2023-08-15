#pragma once

#include<graphics/rendercommands.hpp>
#include<queue>

namespace game::managers{

    class RenderManager{
    public:
        RenderManager() {}
        ~RenderManager() {}

        void Initialize();
        void Shutdown();

        void Clear();
        void SetClearColor(float r, float g, float b, float a);

        // Stores a RenderCommand in the queue
        void Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc);

        // Execute submitted RenderCommands in the order received.
        void Flush();

    private:
        std::queue<std::unique_ptr<graphics::rendercommands::RenderCommand>> mRenderCommands;
    };

}