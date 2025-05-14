// definições do mob "wolf"

#pragma once

#include "core/entity/entity.hpp"

// configurações
constexpr double WOLF_WALK_VELOCITY = 80.0f;
constexpr double WOLF_RUN_VELOCITY = WOLF_WALK_VELOCITY * 1.65f;
constexpr double WOLF_ATTACK_MIN_DISTANCE = 50.0f;

class Wolf : public Entity {
    public:
        Wolf(const Vec2& pos, const Vec2& vel);
        ~Wolf(void) = default;

        void Init(const GraphicsResources& graphicsResources, AppGlobals& globals) override final;

        void Update(AppGlobals& globals, double deltaTime) override final;
        void Render(const GraphicsResources& graphicsResources) override final;
};
