// definições da aplicação

#include "app.hpp"

#include <iostream>

#include "system/global.hpp"
#include "app/global.hpp"

#include "controllers/mob-controller.hpp"

#include "core/object/objects/tree/tree.hpp"

// declarando controllers

MobController mobController = MobController();

//

void App::Initialize(void) {
    // incializando lista de mobs
    globals.mobs.fill(nullptr);

    // inicializando lista de objetos
    globals.objects.fill(nullptr);

    std::shared_ptr<Object> tree = CreateObject<Tree>(200, 200, 10);
    tree->Init(graphicsResources);
    SaveObject<OBJECT_SPAWN_LIMIT>(globals.objects, tree);
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

    // limita o movimento dos mobs
    mobController.LimitMobsMovement();
}

void App::Render(int fps) {
    // renderiza todos os mobs
    mobController.RenderMobs();

    globals.objects[0]->Render(graphicsResources);
}
