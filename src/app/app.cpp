// definições da aplicação

#include "app.hpp"

#include <iostream>

#include "system/global.hpp"
#include "app/global.hpp"

#include "controllers/ambient-controller.hpp"
#include "controllers/mob-controller.hpp"
#include "controllers/collision-controller.hpp"

#include "core/entity/mobs/mobs.hpp"

// declarando controllers
AmbientController ambientController;
MobController mobController;
CollisionController collisionController;

//

void App::Initialize(void) {
    // incializando lista de mobs
    globals.mobs.fill(nullptr);

    // inicializando lista de objetos
    globals.objects.fill(nullptr);

    // pré-geração do ambiente
    ambientController.GenerateAmbient();
}

void App::Shutdown(void) {
    // limpando lista de mobs
    globals.mobs.fill(nullptr);

    // inicializando lista de objetos
    globals.objects.fill(nullptr);
}

//

void App::Update(double deltaTime) {
    // controle de multidão

    // invocação de mobs
    mobController.SpawnMobs(deltaTime);

    // carrega todos os mobs
    mobController.LoadMobs(deltaTime);

    // colisores
    collisionController.MobToMobCollision(deltaTime);
    collisionController.MobToObjectCollision(deltaTime);

    // limita o movimento dos mobs
    mobController.LimitMobsMovement();
}

void App::Render(int fps) {
    // renderiza todos os mobs
    mobController.RenderMobs();

    // renderiza o ambiente
    ambientController.RenderAmbient();
}
