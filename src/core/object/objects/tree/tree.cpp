// definição do objeto árvore

#include "tree.hpp"

Tree::Tree(int x, int y, int size) : Object(x, y, size) {};

//

void Tree::Init(const GraphicsResources& graphicsResources) {
    graphicsResources.imageHandler->CreateImage(graphicsResources.window, "tree", TREE_SPRITE_PATH);
}

void Tree::Render(const GraphicsResources& graphicsResources) {
    // renderiza a árvore
    graphicsResources.imageHandler->RenderImage(graphicsResources.window, "tree", x, y, 0.5f);
}
