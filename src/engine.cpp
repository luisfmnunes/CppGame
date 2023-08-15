#include<engine.hpp>
#include<log.hpp>

#include<graphics/mesh.hpp>
#include<graphics/shader.hpp>

#include<SDL.h>

namespace game{

    void Engine::Run(){
        
        if(Initialize()){

            mRenderManager.SetClearColor(0.2, 0.33, 0.4, 1);

            // Test Mesh

            float vertices[]{
                -0.5f,  -0.5f,  0.f,
                0.f,     0.5f,  0.f,
                0.5f,   -0.5f,  0.f
            };

            std::shared_ptr<graphics::Mesh> mesh = std::make_shared<graphics::Mesh>(&vertices[0], 3, 3);
            
            // Test Shader
            const char* vertexShader = R"(
                #version 410 core
                layout (location = 0) in vec3 position;
                void main()
                {
                    gl_Position = vec4(position, 1.0);
                }
            )";

            const char* fragmentShader = R"(
                #version 410 core
                out vec4 outColor;
                void main()
                {
                    outColor = vec4(1.0);
                }
            )";

            std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader>(vertexShader, fragmentShader);

            while(mIsRunning){
                mWindow.PumpEvents();

                mWindow.BeginRender();

                auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mesh, shader);
                mRenderManager.Submit(std::move(rc));
                mRenderManager.Flush();

                mWindow.EndRender();
            }

            Shutdown();

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

                // Initialize Managers
                mRenderManager.Initialize();

                ret = true;
                mIsRunning = true;
                mIsInitialized = true;
            }
        }

        if(!ret)
            Shutdown();

        return ret;
    }

    void Engine::Shutdown(){
        
        mIsRunning = false;
        mIsInitialized = false;

        // Shutdown Managers
        mRenderManager.Shutdown();
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