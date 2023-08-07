#include <iostream>
#include <engine.hpp>

int main(int argc, char** argv){

    game::Engine engine = game::Engine::GetInstance();
    engine.Initialize();


    std::cout << "Press ENTER to continue...";
    std::cin.ignore();

    return EXIT_SUCCESS;
}