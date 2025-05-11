// aglutina recursos globais para fácil importação

#pragma once

#include <memory>

#include "system/graphics/window.hpp"
#include "system/graphics/image-handler.hpp"

// recursos gráficos
struct GraphicsResources {
    std::shared_ptr<Window> window;
    std::shared_ptr<ImageHandler> imageHandler;
};
