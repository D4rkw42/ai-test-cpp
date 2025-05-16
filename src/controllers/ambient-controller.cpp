// gerencia a geração de ambiente

#include "ambient-controller.hpp"

#include <iostream>
#include <effolkronium/random.hpp>

#include "system/global.hpp"
#include "app/global.hpp"

#include "utils/math/math.hpp"

#include "core/object/objects/objects.hpp"

using random = effolkronium::random_static;

//

void AmbientController::GenerateAmbient(void) {
    int windowWidth, windowHeight;
    window->GetWindowSize(windowWidth, windowHeight);

    int attempts = 0;

    for (int i = 0; i < OBJECT_SPAWN_LIMIT; ++i) {
        // caso não haja espaço para invocar mais objetos
        if (attempts > OBJECT_SPAWN_LIMIT * 0.5f) {
            break;
        }

        double x = random::get<double>(50, windowWidth - 50);
        double y = random::get<double>(50, windowHeight - 50);

        // chance de gerar objetos (garante ao menos metade deles)
        if (!random::get<bool>(0.8f) && i + 1 > OBJECT_SPAWN_LIMIT * 0.5f) {
            continue;
        }

        // se tiver uma árvore muito perto, não gera
        if (FindObjectNear("tree", x, y, MIN_TREE_NEAR_DISTANCE)) {
            i--;
            attempts++;
            continue;
        }

        attempts = 0;

        bool spawnTree = random::get<bool>(0.65f);

        std::shared_ptr<Object> mObject;

        if (spawnTree) {
            mObject = CreateObject<Tree>(x, y, OBJECT_SIZE);
        } else {
            mObject = CreateObject<Bush>(x, y, OBJECT_SIZE);
        }

        mObject->Init(graphicsResources);
        SaveObject<OBJECT_SPAWN_LIMIT>(globals.objects, mObject);
    }
}

void AmbientController::RenderAmbient(void) {
    for (const std::shared_ptr<Object>& object : globals.objects) {
        if (object != nullptr) {
            object->Render(graphicsResources);
        }
    }
}

// utility

bool AmbientController::FindObjectNear(const std::string &type, double x, double y, double reference) {
    for (const std::shared_ptr<Object>& object : globals.objects) {
        if (object != nullptr) {
            if (object->type == type && distance(object->x, object->y, x, y) < reference) {
                return true;
            }
        }
    }

    return false;
}
