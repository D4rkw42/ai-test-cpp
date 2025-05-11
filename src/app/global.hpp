// variáveis globais da aplicação

#pragma once

#include <memory>
#include <vector>

#include "core/entity/entity.hpp"

// configs

constexpr int MOB_SPAWN_LIMIT = 50;

//

inline EntityList<MOB_SPAWN_LIMIT> mobs; // lista de todos os mobs invocados
