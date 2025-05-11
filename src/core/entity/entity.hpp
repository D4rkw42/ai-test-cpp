// definições gerais de uma entidade

#pragma once

#include <memory>
#include <string>
#include <array>

#include "system/resources.hpp"

#include "utils/math/math.hpp"
#include "utils/game/entity/animation.hpp"

// forward declaration para manipulador de comportamento
class BehaviorHandler;

// Classe básica para entidade
class Entity {
    public:
        std::string type;
        std::shared_ptr<std::string> state, prevState;

        int ID = 0;

        Vec2 pos, vel;
        int dir = -1;

        BehaviorHandler* behaviors;
        AnimationHandler animationHandler;

        Entity(const std::string& type, const std::string& state, const Vec2& pos, const Vec2& vel);
        Entity(void);

        ~Entity(void);

        // inicialização geral da entidade. Deve ser chamada apenas uma vez.
        virtual void Init(const GraphicsResources& graphicsResources);

        virtual void Update(double deltaTime); // atualiza as definições da criatura
        virtual void Render(const GraphicsResources& graphicsResources); // renderiza a criatura

        // utility

        // atualização e leitura de estado
        void SetState(const std::string& state);
        const std::string_view GetState(void) const;
        const std::string_view GetPrevState(void) const;
};

// definição para vetor de entidades
template <int limit>
using EntityList = std::array<std::shared_ptr<Entity>, limit>;


// criação/destruição dinâmica de entidades

template <class EntityType>
inline std::shared_ptr<Entity> CreateEntity(double x, double y, double velX = 0.0f, double velY = 0.0f) {
    std::shared_ptr<EntityType> mEntity = std::make_shared<EntityType>(Vec2 { x, y }, Vec2 { velX, velY });
    return std::dynamic_pointer_cast<Entity>(mEntity);
}

template <int entityListLimit>
inline void SaveEntity(EntityList<entityListLimit>& list, const std::shared_ptr<Entity>& entity) {
    for (int i = 0; i < entityListLimit; ++i) {
        if (list[i] == nullptr) {
            list[i] = entity;
            return;
        }
    }
}

template <int entityListLimit>
inline void DestroyEntity(EntityList<entityListLimit>& list, int ID) {
    list[ID] = nullptr;
}
