// gerencia as colisões

#pragma once

// fator de afastamento de colisão
constexpr double COLLISION_OFFSET_BASE = 10.0f;

class CollisionController {
    public:
        // colisão entre mobs
        void MobToMobCollision(double deltaTime);

        // colisão entre mobs e objetos
        void MobToObjectCollision(double deltaTime);
};
