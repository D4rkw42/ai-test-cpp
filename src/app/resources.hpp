// definição de recursos globais

#pragma once

#include <memory>

#include "app/configs.hpp"

#include "core/entity/entity.hpp"
#include "core/object/object.hpp"

// define o ambiente de acesso do recursos globais de app
struct AppGlobals {
    EntityList<MOB_SPAWN_LIMIT> mobs; // lista de mobs
    ObjectList<OBJECT_SPAWN_LIMIT> objects; // lista de objetos
};
