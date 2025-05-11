// inicialização e finalização de bibliotecas e subsistemas

#include "subsystems.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

// biblioteca SDL2
void InitializeSDL2(void) {
    int SDLInitSuccess = SDL_Init(SDL_INIT_VIDEO);

    if (SDLInitSuccess < 0) {
        std::cerr << "Couldn't initialize SDL2: " << SDL_GetError();
        throw;
    }

    int SDLImageInitSuccess = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    if (SDLImageInitSuccess == 0) {
        std::cerr << "Couldn't initialize SDL2 Image: " << SDL_GetError();
        throw;
    }
}

void ShutdownSDL2(void) {
    IMG_Quit();
    SDL_Quit();
}

//

void InitializeSubsystems(void) {
    InitializeSDL2();
}

void ShutdownSubsystems(void) {
    ShutdownSDL2();
}
