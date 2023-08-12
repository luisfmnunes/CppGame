#include<core/window.hpp>
#include<engine.hpp>

#include<glad/glad.h>
#include<SDL.h>
#include<log.hpp>

namespace game::core{

    Window::Window() : mWindow(nullptr) {}
    Window::~Window(){ if(mWindow) Shutdown(); }

    bool Window::Create(){
        mWindow = SDL_CreateWindow("GameCpp", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        if(!mWindow) {
            
            LOG_ERROR("Error creating window: {}", SDL_GetError());
            LOG_ASSERT(mWindow, "Failed to Create SDL_Window");

            return false;
        }

#ifdef __APPLE__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        SDL_SetWindowMinimumSize(mWindow, 200, 200);

        mGLContext = SDL_GL_CreateContext(mWindow);
        if (mGLContext == nullptr){
            LOG_ERROR("Error creating OpenGL Context: {}", SDL_GetError());
            return false;
        }

        gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);

        // TODO: Move to render initialization
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);

        glClearColor(0, 0, 0, 255);
        // End TODO

        return true;
    }

    void Window::Shutdown(){
        SDL_DestroyWindow(mWindow);
        std::string sdl_return(SDL_GetError());
        if(!sdl_return.empty()) LOG_ERROR("Failed to Destroy Window: {}", sdl_return.c_str());
        mWindow = nullptr;
    }
    
    void Window::PumpEvents(){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_EVENT_QUIT:
                    Engine::GetInstance().Quit();
                    break;

                default:
                    break;
            }
        }
    }

    void Window::BeginRender(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::EndRender(){
        SDL_GL_SwapWindow(mWindow);
    }
}