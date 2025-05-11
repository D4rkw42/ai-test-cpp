// funções para gerenciar entidades

#include "mob-controller.hpp"

#include <effolkronium/random.hpp>

#include "system/global.hpp"
#include "app/global.hpp"

#include "core/entity/entity.hpp"
#include "core/entity/mobs/wolf/wolf.hpp"

//

using random = effolkronium::random_static;

//

MobController::MobController(void) {}
MobController::~MobController(void) {}

//

void MobController::LoadMobs(double deltatime) {
    for (std::shared_ptr<Entity>& mob : mobs) {
        if (mob != nullptr) {
            mob->Update(deltatime);
        }  
    }
}

void MobController::RenderMobs(void) {
    for (std::shared_ptr<Entity>& mob : mobs) {
        if (mob != nullptr) {
            mob->Render(graphicsResources);
        }
    }
}

void MobController::SpawnMobs(double deltaTime) {
    static double spawnMobsIn = 0.0f;
    spawnMobsIn -= deltaTime;

    if (spawnMobsIn <= 0) {
        spawnMobsIn = SPAWN_MOB_COOLDOWN;

        // porcentagem de chance para spawnar mobs
        if (!random::get<bool>(0.7f)) {
            return;
        }

        bool spawnWolf = random::get<bool>(0.5f);

        int windowWidth, windowHeight;
        window->GetWindowSize(windowWidth, windowHeight);

        double x = random::get<double>(0, windowWidth);
        double y = random::get<double>(0, windowHeight);

        if (spawnWolf) {
            // spawns wolf
            std::shared_ptr<Entity> mWolf = CreateEntity<Wolf>(x, y);
            mWolf->Init(graphicsResources);
            SaveEntity<MOB_SPAWN_LIMIT>(mobs, mWolf);
        } else {
            // spawns sheep
        }
    }
}

void MobController::LimitMobsMovement(void) {
    for (std::shared_ptr<Entity>& mob : mobs) {
        if (mob != nullptr) {
            int windowWidth, windowHeight;
            window->GetWindowSize(windowWidth, windowHeight);

            // eixo horizontal

            if (mob->pos.Get(0) < MOB_MOV_LIMIT_HORIZONTAL_REF) {
                mob->pos.Set(0, MOB_MOV_LIMIT_HORIZONTAL_REF);
            } else if (mob->pos.Get(0) > windowWidth - MOB_MOV_LIMIT_HORIZONTAL_REF) {
                mob->pos.Set(0, windowWidth - MOB_MOV_LIMIT_HORIZONTAL_REF);
            }

            // eixo vertical

            if (mob->pos.Get(1) < MOB_MOV_LIMIT_VERTICAL_REF) {
                mob->pos.Set(1, MOB_MOV_LIMIT_VERTICAL_REF);
            } else if (mob->pos.Get(1) > windowHeight - MOB_MOV_LIMIT_VERTICAL_REF) {
                mob->pos.Set(1, windowHeight - MOB_MOV_LIMIT_VERTICAL_REF);
            }
        }
    }
}
