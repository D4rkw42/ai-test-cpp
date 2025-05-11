// definições do mob "wolf"

#include "bunny.hpp"

#include <iostream>

#include <effolkronium/random.hpp>

#include "system/resources.hpp"

#include "utils/game/entity/behavior-handler.hpp"
#include "utils/math/math.hpp"

using random = effolkronium::random_static;

// Comportamentos
static void GlobalBehaviors(Entity* bunny, AppGlobals& globals, double deltaTime) {
    // atualiza a posição
    bunny->pos += bunny->vel * deltaTime;
}

static BehaviorCallback Walk(void) {
    constexpr double NEXT_STATE_IN = 5.0f;

    double nextStateIn = NEXT_STATE_IN;
    double findNextLocationIn = 0;
    double walkAngle;

    return [NEXT_STATE_IN, nextStateIn, findNextLocationIn, walkAngle](Entity* bunny, double deltaTime, const NextBehaviorCaller& Next) mutable {
        bunny->animationHandler.StartAnimation("bunny-walk");

        bunny->dir = (bunny->vel.Get(0) < 0)? -1 : 1;

        nextStateIn -= deltaTime;

        // mudança de estado por sorteio
        if (nextStateIn <= 0) {
            nextStateIn = NEXT_STATE_IN;

            // chance de ficar parado
            if (random::get<bool>(0.3f)) {
                return Next("idle");
            }
        }

        findNextLocationIn -= deltaTime;

        // alterando direção
        if (findNextLocationIn <= 0) {
            walkAngle = random::get<double>(0, 2 * PI);
            findNextLocationIn = random::get<double>(3.0f, 7.0f);
        }

        // atualizando velocidade de acordo
        bunny->MoveTorwards(BUNNY_WALK_VELOCITY, walkAngle);
    };
}

static BehaviorCallback Escape(void) {
    return [&](Entity* bunny, double deltaTime, const NextBehaviorCaller& Next) mutable {
        
    };
}

static BehaviorCallback Idle(void) {
    bool enteredIdleState = false;
    double startWalkigIn = 2.5f;

    return [startWalkigIn, enteredIdleState](Entity* bunny, double deltaTime, const NextBehaviorCaller& Next) mutable {
        bunny->animationHandler.StartAnimation("bunny-idle");
        bunny->vel *= 0;

        if (!enteredIdleState) {
            enteredIdleState = true;

            bunny->dir = random::get<int>({ -1, 1 });
        }

        startWalkigIn -= deltaTime;

        if (startWalkigIn <= 0) {
            startWalkigIn = random::get<double>(6.0f, 12.0f);
            return Next("walking");
        }
    };
}

static void RegisterBehaviors(Bunny* bunny) {
    bunny->behaviors->CreateBehavior("walking", Walk());
    bunny->behaviors->CreateBehavior("idle", Idle());
    bunny->behaviors->CreateBehavior("escaping", Escape());
}

// Animação

static void RegisterAnimations(const GraphicsResources& graphicsResources, Bunny* bunny) {
    bunny->animationHandler.RegisterAnimation(graphicsResources, "bunny-walk", "bunny/walking.png", 4, 0.4f);
    bunny->animationHandler.RegisterAnimation(graphicsResources, "bunny-idle", "bunny/idle.png", 2, 1.2f);
}

//

Bunny::Bunny(const Vec2& pos, const Vec2& vel) : Entity("bunny", (random::get<bool>(0.6f))? "idle" : "walking", pos, vel) {}

//

void Bunny::Init(const GraphicsResources& graphicsResources, AppGlobals& globals) {
    RegisterBehaviors(this);
    RegisterAnimations(graphicsResources, this);
}

void Bunny::Update(AppGlobals& globals, double deltaTime) {
    // atualiza os comportamentos
    this->behaviors->UpdateBehaviors(this, deltaTime);

    // carrega o comportamento
    this->behaviors->LoadBehavior(this, deltaTime);

    // comportamentos globais
    GlobalBehaviors(this, globals, deltaTime);

    // carrega das animações
    this->animationHandler.LoadAnimation(deltaTime);
}

void Bunny::Render(const GraphicsResources& graphicsResources) {
    // renderiza a animação
    this->animationHandler.DisplayAnimation(graphicsResources, this->pos.Get(0), this->pos.Get(1), 1.2f, (this->dir == -1));
}
