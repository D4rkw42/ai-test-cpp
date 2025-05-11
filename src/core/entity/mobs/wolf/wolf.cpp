// definições do mob "wolf"

#include "wolf.hpp"

#include <iostream>

#include <effolkronium/random.hpp>

#include "system/resources.hpp"

#include "utils/game/entity/behavior-handler.hpp"
#include "utils/math/math.hpp"

using random = effolkronium::random_static;

// Comportamentos
static BehaviorCallback Walk(void) {
    constexpr double NEXT_STATE_IN = 5.0f;

    double nextStateIn = NEXT_STATE_IN;
    double findNextLocationIn = 0;
    Vec2 walkVel;

    return [NEXT_STATE_IN, nextStateIn, findNextLocationIn, walkVel](Entity* wolf, double deltaTime, const NextBehaviorCaller& Next) mutable {
        wolf->animationHandler.StartAnimation("wolf-walk");

        wolf->dir = (wolf->vel.Get(0) < 0)? -1 : 1;

        nextStateIn -= deltaTime;

        // mudança de estado por sorteio
        if (nextStateIn <= 0) {
            nextStateIn = NEXT_STATE_IN;

            // chance de ficar parado
            if (random::get<bool>(0.3f)) {
                return Next("idle");
            }

            // chance de correr
            if (random::get<bool>(0.15f)) {
                return Next("running");
            }
        }

        findNextLocationIn -= deltaTime;

        // alterando direção
        if (findNextLocationIn <= 0) {
            walkVel = Vec2(
                WOLF_WALK_VELOCITY * random::get<double>(-1, 1),
                WOLF_WALK_VELOCITY * random::get<double>(-1, 1)
            );

            findNextLocationIn = random::get<double>(3.0f, 7.0f);
        }

        // atualizando velocidade de acordo
        wolf->vel = walkVel;
    };
}

static BehaviorCallback Run(void) {
    bool enteredRunState = false;

    return [enteredRunState](Entity* wolf, double deltaTime, const NextBehaviorCaller& Next) mutable {
        wolf->animationHandler.StartAnimation("wolf-run");

        if (!enteredRunState) {
            enteredRunState = true;

            wolf->vel = Vec2(
                WOLF_RUN_VELOCITY * random::get<double>(-1.0f, 1.0f),
                WOLF_RUN_VELOCITY * random::get<double>(-1.0f, 1.0f)
            );
        }

        wolf->dir = (wolf->vel.Get(0) < 0)? -1 : 1;
    };
}

static BehaviorCallback Chase(void) {
    return [&](Entity* wolf, double deltaTime, const NextBehaviorCaller& Next) mutable {
        
    };
}

static BehaviorCallback Idle(void) {
    bool enteredIdleState = false;
    double startWalkigIn = 2.5f;

    return [startWalkigIn, enteredIdleState](Entity* wolf, double deltaTime, const NextBehaviorCaller& Next) mutable {
        wolf->animationHandler.StartAnimation("wolf-idle");
        wolf->vel *= 0;

        if (!enteredIdleState) {
            enteredIdleState = true;

            wolf->dir = random::get<int>({ -1, 1 });
        }

        startWalkigIn -= deltaTime;

        if (startWalkigIn <= 0) {
            startWalkigIn = random::get<double>(6.0f, 12.0f);
            return Next("walking");
        }
    };
}

static void RegisterBehaviors(Wolf* wolf) {
    wolf->behaviors->CreateBehavior("walking", Walk());
    wolf->behaviors->CreateBehavior("idle", Idle());
    wolf->behaviors->CreateBehavior("running", Run(), NextBehavior("idle", 4.0f));
}

// Animação

static void RegisterAnimations(const GraphicsResources& graphicsResources, Wolf* wolf) {
    wolf->animationHandler.RegisterAnimation(graphicsResources, "wolf-walk", "wolf/walking.png", 5, 0.6f);
    wolf->animationHandler.RegisterAnimation(graphicsResources, "wolf-run", "wolf/running.png", 5, 0.5f);
    wolf->animationHandler.RegisterAnimation(graphicsResources, "wolf-idle", "wolf/idle.png", 2, 1.5f);
    wolf->animationHandler.RegisterAnimation(graphicsResources, "wolf-attack", "wolf/attack.png", 5, 0.6f, false);
}

//

Wolf::Wolf(const Vec2& pos, const Vec2& vel) : Entity("wolf", (random::get<bool>(0.6f))? "idle" : "walking", pos, vel) {}

//

void Wolf::Init(const GraphicsResources& graphicsResources) {
    RegisterBehaviors(this);
    RegisterAnimations(graphicsResources, this);
}

void Wolf::Update(double deltaTime) {
    // atualiza os comportamentos
    this->behaviors->UpdateBehaviors(this, deltaTime);

    // carrega o comportamento
    this->behaviors->LoadBehavior(this, deltaTime);

    // comportamentos globais
    this->pos += this->vel * deltaTime;

    // carrega das animações
    this->animationHandler.LoadAnimation(deltaTime);
}

void Wolf::Render(const GraphicsResources& graphicsResources) {
    // renderiza a animação
    this->animationHandler.DisplayAnimation(graphicsResources, this->pos.Get(0), this->pos.Get(1), 1.2f, (this->dir != -1));
}
