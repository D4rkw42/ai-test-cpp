// definição para o objeto "Habbit Hole"

#include "bush.hpp"

Bush::Bush(int x, int y, int size) : Object("bush", x, y, size) {}

void Bush::Init(const GraphicsResources& graphicsResources) {
    graphicsResources.imageHandler->CreateImage(graphicsResources.window, "habbit-hole", "assets/sprites/objects/bush.png");
}

void Bush::Render(const GraphicsResources& graphicsResources) {
    graphicsResources.imageHandler->RenderImage(graphicsResources.window, "habbit-hole", x, y, 0.4f);
}
