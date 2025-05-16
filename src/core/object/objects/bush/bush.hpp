// definição para o objeto "Bush"

#pragma once

#include "core/object/object.hpp"

class Bush : public Object {
    public:
        Bush(int x, int y, int size);
        ~Bush() = default;

        void Init(const GraphicsResources& graphicsResources) override final;
        void Render(const GraphicsResources& graphicsResources) override final;
};
