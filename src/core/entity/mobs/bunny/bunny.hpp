// definições do mob "bunny"

#pragma once

#include "core/entity/entity.hpp"

// configurações
constexpr double BUNNY_WALK_VELOCITY = 60.0f;

class Bunny : public Entity {
    public:
        Bunny(const Vec2& pos, const Vec2& vel);
        ~Bunny(void) = default;

        void Init(const GraphicsResources& graphicsResources, AppGlobals& globals) override final;

        void Update(AppGlobals& globals, double deltaTime) override final;
        void Render(const GraphicsResources& graphicsResources) override final;
};
