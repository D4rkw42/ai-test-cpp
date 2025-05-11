// definições da aplicação

#include "app.hpp"

#include <iostream>

#include "system/global.hpp"
#include "app/global.hpp"

#include "controllers/mob-controller.hpp"

// declarando controllers

MobController mobController = MobController();

//

void App::Initialize(void) {
    // incializando lista de mobs
    globals.mobs.fill(nullptr);
}

void App::Shutdown(void) {
    // limpando lista de mobs
    globals.mobs.fill(nullptr);
}

//

void App::Update(double deltaTime) {
    // controle de multidão

    // invocação de mobs
    mobController.SpawnMobs(deltaTime);

    // carrega todos os mobs
    mobController.LoadMobs(deltaTime);

    // limita o movimento dos mobs
    mobController.LimitMobsMovement();
}

void App::Render(int fps) {
    // renderiza todos os mobs
    mobController.RenderMobs();
}
