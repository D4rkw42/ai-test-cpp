// definição do objeto "Tree"

#pragma once

#include "system/resources.hpp"
#include "core/object/object.hpp"

constexpr const char* TREE_SPRITE_PATH = "assets/sprites/objects/tree.png";

class Tree : public Object {
    public:
        Tree(int x, int y, int size);
        ~Tree() = default;

        void Init(const GraphicsResources& graphicsResources) override final;
        void Render(const GraphicsResources& graphicsResources) override final;
};
