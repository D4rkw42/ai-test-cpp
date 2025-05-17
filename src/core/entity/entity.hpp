// definições gerais de uma entidade

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <array>

#include "system/resources.hpp"

#include "utils/math/math.hpp"
#include "utils/game/entity/animation.hpp"

// forward declaration para manipulador de comportamento
class BehaviorHandler;

// forward declaration para os recursos globais
struct AppGlobals;

// Classe básica para entidade
class Entity {
    public:
        std::string type;
        std::shared_ptr<std::string> state, prevState;

        int ID = 0;

        Vec2 pos, vel;
        int dir = -1;

        // tamanho de uma entidade
        int size;

        // uma entidade considerada inválida pode ser eliminada automaticamente pelo ecossistema da aplicação
        bool invalid = false;

        BehaviorHandler* behaviors;
        AnimationHandler animationHandler;

        Entity(const std::string& type, const std::string& state, const Vec2& pos, const Vec2& vel, int size);
        Entity(void);

        ~Entity();

        // inicialização geral da entidade. Deve ser chamada apenas uma vez.
        virtual void Init(const GraphicsResources& graphicsResources, AppGlobals& globals);

        virtual void Update(AppGlobals& globals, double deltaTime); // atualiza as definições da criatura
        virtual void Render(const GraphicsResources& graphicsResources); // renderiza a criatura

        // utility

        // atualização e leitura de estado
        void SetState(const std::string& state);
        const std::string_view GetState(void) const;
        const std::string_view GetPrevState(void) const;

        // torna uma entidade inválida
        void Eliminate(void);
        
        static double GetDistance(const std::shared_ptr<Entity>& e1, const std::shared_ptr<Entity>& e2);
        static double GetDistance(Entity* e1, Entity* e2);
        static bool IsColliding(const std::shared_ptr<Entity>& e1, const std::shared_ptr<Entity>& e2);

        // movimento
        void MoveTorwards(double vel, double angle);
};

// definição para vetor de entidades
template <int EntityListLimit>
using EntityList = std::array<std::shared_ptr<Entity>, EntityListLimit>;


// criação/destruição dinâmica de entidades

template <class EntityType>
inline std::shared_ptr<Entity> CreateEntity(double x, double y, double velX = 0.0f, double velY = 0.0f) {
    std::shared_ptr<EntityType> mEntity = std::make_shared<EntityType>(Vec2 { x, y }, Vec2 { velX, velY });
    return std::dynamic_pointer_cast<Entity>(mEntity);
}

template <int EntityListLimit>
inline void SaveEntity(EntityList<EntityListLimit>& list, const std::shared_ptr<Entity>& entity) {
    for (int i = 0; i < EntityListLimit; ++i) {
        if (list[i] == nullptr) {
            list[i] = entity;
            list[i]->ID = i;
            return;
        }
    }
}

template <int EntityListLimit>
inline void DestroyEntity(EntityList<EntityListLimit>& list, int ID) {
    list[ID] = nullptr;
}
