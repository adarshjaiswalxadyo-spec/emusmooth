#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Emulator.h"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    try {
        Emulator emulator;

        if (!emulator.Initialize()) {
            std::cerr << "Failed to initialize emulator!" << std::endl;
            return 1;
        }

        emulator.Run();
        emulator.Shutdown();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}

