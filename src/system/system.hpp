// configurações do sistema

#pragma once

#include <SDL2/SDL.h>

#define SDL_MAIN_HANDLED

class System {
    public:
        void Initialize(void);
        void Shutdown(void);

        // Inicia a aplicação básica
        void Run(void);
};
