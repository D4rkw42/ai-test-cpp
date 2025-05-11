// definições para renderização de imagens

#include "image-handler.hpp"

#include <iostream>

#include <SDL2/SDL_image.h>

ImageHandler::ImageHandler(void) {}

ImageHandler::~ImageHandler(void) {
    for (const auto& [_, image] : this->collection) {
        SDL_DestroyTexture(image->texture);
    }
}

//

void ImageHandler::CreateImage(const std::shared_ptr<Window>& window, const std::string& name, const char* path) {
    // verifica se a imagem já existe
    if (this->collection.find(name) != this->collection.end()) {
        return;
    }

    SDL_Surface* surface = IMG_Load(path);

    if (surface == NULL) {
        std::cerr << "Cannot load surface for path: " << path << " for reason: " << SDL_GetError() << "\n";
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->GetWindowRenderer(), surface);

    if (texture == NULL) {
        std::cerr << "Cannot load texture for path: " << path << " for reason: " << SDL_GetError() << "\n";
        return;
    }

    int width = surface->w;
    int height = surface->h;

    std::shared_ptr<Image> image = std::make_shared<Image>();

    image->texture = texture;
    image->width = width;
    image->height = height;

    this->collection[name] = image;

    SDL_FreeSurface(surface);
}

//

void ImageHandler::RenderImage(const std::shared_ptr<Window>& window, const std::string& name, int x, int y, double scale, bool flip) {
    const std::shared_ptr<Image> mImage = this->collection[name];

    SDL_Texture* texture = mImage->texture;
    
    int
        width = mImage->width * scale,
        height = mImage->height * scale;

    x -= width / 2;
    y -= height / 2;

    SDL_Rect rect { x, y, width, height };

    //SDL_RenderCopy(window->GetWindowRenderer(), texture, NULL, &rect);
    SDL_RenderCopyEx(window->GetWindowRenderer(), texture, NULL, &rect, 0.0f, NULL, flip? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void ImageHandler::RenderImage(const std::shared_ptr<Window>& window, const std::string& name, int x, int y, int cropX, int cropY, int cropW, int cropH, double scale, bool flip) {
    const std::shared_ptr<Image> mImage = this->collection[name];

    SDL_Texture* texture = mImage->texture;
    
    int
        width = (cropW - 1) * scale,
        height = cropH * scale;

    x -= width / 2;
    y -= height / 2;

    SDL_Rect fillRect { x, y, width, height };
    SDL_Rect cropRect { cropX, cropY, cropW, cropH };

    //SDL_RenderCopy(window->GetWindowRenderer(), texture, &cropRect, &fillRect);
    SDL_RenderCopyEx(window->GetWindowRenderer(), texture, &cropRect, &fillRect, 0.0f, NULL, flip? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
