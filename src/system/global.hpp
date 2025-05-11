// variáveis globais do sistema

#pragma once

#include <memory>

#include "system/graphics/window.hpp"
#include "system/graphics/image-handler.hpp"

#include "system/resources.hpp"

inline std::shared_ptr<Window> window = nullptr; // janela global
inline std::shared_ptr<ImageHandler> imageHandler = std::make_shared<ImageHandler>(); // faz o gerenciamento de imagens e sua renderização

// declaração dos recursos globais
inline GraphicsResources graphicsResources; // recursos gráficos
