// funções para gerenciar entidades

#pragma once

// configurações
constexpr double SPAWN_MOB_COOLDOWN = 3.0f;

// limite do mapa
constexpr int MOB_MOV_LIMIT_HORIZONTAL_REF = 64;
constexpr int MOB_MOV_LIMIT_VERTICAL_REF = 32;

// gerencia todas as entidades
class MobController {
    public:
        MobController(void);
        ~MobController(void);

        //

        // carrega/renderiza todos os mobs
        void LoadMobs(double deltaTime);
        void RenderMobs(void);

        // spawna mobs aleatoriamente
        void SpawnMobs(double deltaTime);

        // limita o movimentos do mobs no mapa
        void LimitMobsMovement(void);
};
