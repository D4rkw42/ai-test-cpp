// definições de janela

#pragma once

#include <SDL2/SDL.h>

#include <string>

// classe geral para criar janelas
class Window {
    public:
        Window(const std::string& name, int width, int height);
        ~Window();

        void Clear(void); // limpa a janela
        void Render(void); // renderiza todas as renquisições de renderização

        // utility
        SDL_Window* GetRawWindow(void) const;
        SDL_Renderer* GetWindowRenderer(void) const;
        void GetWindowSize(int& width, int& height) const;

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};
