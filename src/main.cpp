#include <iostream>
#include <engine.hpp>
#include <SDL_main.h>

int main(int argc, char** argv){

    game::Engine& engine = game::Engine::GetInstance();
    engine.Run();

    std::cout << "Press ENTER to continue...";
    std::cin.ignore();

    return EXIT_SUCCESS;
}