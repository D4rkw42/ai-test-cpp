// definições de janela

#include "window.hpp"

#include <iostream>

Window::Window(const std::string& name, int width, int height) {
    this->window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    if (this->window == NULL) {
        std::cerr << "Couldn't create a window: " << SDL_GetError() << "\n";
        throw;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    if (this->renderer == NULL) {
        std::cerr << "Couldn't create a window(renderer): " << SDL_GetError() << "\n";
        throw;
    }
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

//

void Window::Clear(void) {
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->renderer);
}

void Window::Render(void) {
    SDL_RenderPresent(this->renderer);
}

// utility
SDL_Window *Window::GetRawWindow(void) const {
    return this->window;
}

SDL_Renderer *Window::GetWindowRenderer(void) const {
    return this->renderer;
}

void Window::GetWindowSize(int& width, int& height) const {
    int w, h;
    SDL_GetWindowSize(this->window, &w, &h);

    width = w;
    height = h;
}
