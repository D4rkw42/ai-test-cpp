// definições para renderização de imagens

#pragma once

#include <memory>
#include <unordered_map>
#include <string>

#include <SDL2/SDL.h>

#include "system/graphics/window.hpp"

// definição geral de imagem
struct Image {
    SDL_Texture* texture;
    int width, height;
};

// key-map para armazenas imagens
typedef std::unordered_map<std::string, std::shared_ptr<Image>> ImageCollection; // <ImageName, Image>

class ImageHandler {
    public:
        ImageHandler(void);
        ~ImageHandler(void);

        void CreateImage(const std::shared_ptr<Window>& window, const std::string& name, const char* path);

        void RenderImage(const std::shared_ptr<Window>& window, const std::string& name, int x, int y, double scale = 1.0f, bool flip = false);
        void RenderImage(const std::shared_ptr<Window>& window, const std::string& name, int x, int y, int cropX, int cropY, int cropW, int cropH, double scale = 1.0f, bool flip = false);

        // obtém uma imagem
        inline std::shared_ptr<Image> GetImage(const std::string& name) {
            return this->collection[name];
        }

    private:
        ImageCollection collection;
};
