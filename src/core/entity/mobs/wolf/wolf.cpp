// definições do mob "wolf"

#include "wolf.hpp"

#include <iostream>

#include <effolkronium/random.hpp>

#include "system/resources.hpp"
#include "app/resources.hpp"

#include "utils/game/entity/behavior-handler.hpp"
#include "utils/math/math.hpp"

using random = effolkronium::random_static;

// Comportamentos
static void GlobalBehaviors(Entity* wolf, AppGlobals& globals, double deltaTime) {
    // atualiza a posição
    wolf->pos += wolf->vel * deltaTime;

    // sistema para iniciar ataque os coelhos
    if (wolf->GetState() != "attack") {
        for (const std::shared_ptr<Entity>& mob : globals.mobs) {
            if (mob != nullptr) {
                if (mob->type == "bunny" && Entity::GetDistance(wolf, mob.get()) <= WOLF_ATTACK_MIN_DISTANCE) {
                    wolf->SetState("attack");
                }
            }
        }
    }
}

static BehaviorCallback Walk(void) {
    constexpr double NEXT_STATE_IN = 5.0f;

    double nextStateIn = NEXT_STATE_IN;
    double findNextLocationIn = 0;
    double walkAngle;

    return [NEXT_STATE_IN, nextStateIn, findNextLocationIn, walkAngle](Entity* wolf, double deltaTime, const NextBehaviorCaller& Next) mutable {
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
            if (random::get<bool>(0.4f)) {
                return Next("running");
            }
        }

        findNextLocationIn -= deltaTime;

        // alterando direção
        if (findNextLocationIn <= 0) {
            walkAngle = random::get<double>(0, 2 * PI);
            findNextLocationIn = random::get<double>(3.0f, 7.0f);
        }

        // atualizando velocidade de acordo
        wolf->MoveTorwards(WOLF_WALK_VELOCITY, walkAngle);
    };
}

static BehaviorCallback Run(void) {
    bool enteredRunState = false;

    return [enteredRunState](Entity* wolf, double deltaTime, const NextBehaviorCaller& Next) mutable {
        wolf->animationHandler.StartAnimation("wolf-run");

        if (!enteredRunState) {
            enteredRunState = true;

            double angle = random::get<double>(0, 2 * PI);
            wolf->MoveTorwards(WOLF_RUN_VELOCITY, angle);
        }

        wolf->dir = (wolf->vel.Get(0) < 0)? -1 : 1;
    };
}

static BehaviorCallback Chase(void) {
    return [&](Entity* wolf, double deltaTime, const NextBehaviorCaller& Next) mutable {
        
    };
}

static BehaviorCallback Attack(AppGlobals& globals) {
    bool enteredAttackState = false;
    int bunnyID = -1;

    bool bunnyAttacked = false;

    return [&globals, enteredAttackState, bunnyID, bunnyAttacked](Entity* wolf, double deltaTime, const NextBehaviorCaller& Next) mutable {
        wolf->animationHandler.StartAnimation("wolf-attack");
        wolf->vel *= 0;

        // finaliza o ataque
        if (wolf->animationHandler.HasAnimationFinished() && enteredAttackState) {
            wolf->animationHandler.RestartAnimation(); // restarta a animação em caso de posterior chamamento

            enteredAttackState = false;
            bunnyID = -1;
            bunnyAttacked = false;

            return Next("idle");
        }

        if (!enteredAttackState) {
            enteredAttackState = true;

            // encontrando a primeira coelho
            for (int i = 0; i < MOB_SPAWN_LIMIT; ++i) {
                if (globals.mobs[i] != nullptr) {
                    if (globals.mobs[i]->type == "bunny") {
                        bunnyID = globals.mobs[i]->ID;
                        break;
                    }
                }
            }

            // se não houver coelho, volta para o estado idle
            if (bunnyID == -1) {
                enteredAttackState = false;
                return Next("idle");
            }

            // encontrando a coelho mais próxima
            for (int i = bunnyID + 1; i < MOB_SPAWN_LIMIT; ++i) {
                if (globals.mobs[i] != nullptr) {
                    if (globals.mobs[i]->type == "bunny") {
                        if (Entity::GetDistance(wolf, globals.mobs[i].get()) < Entity::GetDistance(wolf, globals.mobs[bunnyID].get())) {
                            bunnyID = globals.mobs[i]->ID;
                        }
                    }
                }
            }
        }

        // se o coelho já foi atacado, stand-by...
        if (bunnyAttacked) {
            return;
        }

        // verifica constantemente se a ovelha porventura não foi eliminada por outro lobo
        if (globals.mobs[bunnyID] == nullptr) {
            enteredAttackState = false;
            bunnyID = -1;
            bunnyAttacked = false;
            return Next("idle");
        }

        // altera a orientação do lobo com base no coelho
        if (globals.mobs[bunnyID]->pos.Get(0) > wolf->pos.Get(0)) {
            wolf->dir = 1;
        } else {
            wolf->dir = -1;
        }

        // atacando o coelho
        if (wolf->animationHandler.GetAnimationTimePercent() >= 0.8f && Entity::GetDistance(wolf, globals.mobs[bunnyID].get()) <= 1.1f * WOLF_ATTACK_MIN_DISTANCE) {
            DestroyEntity<MOB_SPAWN_LIMIT>(globals.mobs, bunnyID);
            bunnyAttacked = true;
        }
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

            // saindo do ataque, permanece a orientação anterior
            if (wolf->GetPrevState() != "attack") {
                wolf->dir = random::get<int>({ -1, 1 });
            }
        }

        startWalkigIn -= deltaTime;

        if (startWalkigIn <= 0) {
            startWalkigIn = random::get<double>(4.0f, 8.0f);
            return Next("walking");
        }
    };
}

static void RegisterBehaviors(Wolf* wolf, AppGlobals& globals) {
    wolf->behaviors->CreateBehavior("walking", Walk());
    wolf->behaviors->CreateBehavior("idle", Idle());
    wolf->behaviors->CreateBehavior("running", Run(), NextBehavior("idle", 4.0f));
    wolf->behaviors->CreateBehavior("attack", Attack(globals));
}

// Animação

static void RegisterAnimations(const GraphicsResources& graphicsResources, Wolf* wolf) {
    wolf->animationHandler.RegisterAnimation(graphicsResources, "wolf-walk", "wolf/walking.png", 5, 0.7f);
    wolf->animationHandler.RegisterAnimation(graphicsResources, "wolf-run", "wolf/running.png", 5, 0.5f);
    wolf->animationHandler.RegisterAnimation(graphicsResources, "wolf-idle", "wolf/idle.png", 2, 1.5f);
    wolf->animationHandler.RegisterAnimation(graphicsResources, "wolf-attack", "wolf/attack.png", 5, 0.6f, false);
}

//

Wolf::Wolf(const Vec2& pos, const Vec2& vel) : Entity("wolf", (random::get<bool>(0.6f))? "idle" : "walking", pos, vel, WOLF_SIZE) {}

//

void Wolf::Init(const GraphicsResources& graphicsResources, AppGlobals& globals) {
    RegisterBehaviors(this, globals);
    RegisterAnimations(graphicsResources, this);
}

void Wolf::Update(AppGlobals& globals, double deltaTime) {
    // atualiza os comportamentos
    this->behaviors->UpdateBehaviors(this, deltaTime);

    // carrega o comportamento
    this->behaviors->LoadBehavior(this, deltaTime);

    // comportamentos globais
    GlobalBehaviors(this, globals, deltaTime);

    // carrega das animações
    this->animationHandler.LoadAnimation(deltaTime);
}

void Wolf::Render(const GraphicsResources& graphicsResources) {
    // renderiza a animação
    this->animationHandler.DisplayAnimation(graphicsResources, this->pos.Get(0), this->pos.Get(1), 0.9f, (this->dir != -1));
}
