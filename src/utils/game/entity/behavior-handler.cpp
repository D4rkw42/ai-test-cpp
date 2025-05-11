// wrapper para gerenciar o comportamento de entidades

#include "behavior-handler.hpp"

#include <iostream>

BehaviorHandler::BehaviorHandler(void) {}
BehaviorHandler::~BehaviorHandler(void) {}

//

void BehaviorHandler::CreateBehavior(const std::string& name, const BehaviorCallback& callback, const NextBehaviorData& nextBehaviorData) {
    if (this->behaviorList.find(name) != this->behaviorList.end()) {
        return;
    }

    this->behaviorList[name] = CreateBehaviorObject(callback, nextBehaviorData);
}

void BehaviorHandler::CreateBehavior(const std::string& name, const BehaviorCallback& callback) {
    if (this->behaviorList.find(name) != this->behaviorList.end()) {
        return;
    }

    this->behaviorList[name] = CreateBehaviorObject(callback, NextBehavior("none"));
}

//

void BehaviorHandler::LoadBehavior(Entity* entity, double deltaTime) {
    std::shared_ptr<Behavior> behavior = FindEntityBehavior(entity);

    // função para passar de estado internamento ao comportamento
    const NextBehaviorCaller Next = [&, this](const std::string& nextBehaviorName) {
        this->ChangeEntityBehavior(entity, nextBehaviorName);
    };

    behavior->callback(entity, deltaTime, Next);

    if (behavior->next.nextBehaviorName != "none" && behavior->next.duration == -1) {
        ChangeEntityBehavior(entity, behavior->next.nextBehaviorName);
    }
}

void BehaviorHandler::UpdateBehaviors(Entity* entity, double deltaTime) {
    std::shared_ptr<Behavior> behavior = FindEntityBehavior(entity);

    if (behavior->next.nextBehaviorName == "none") {
        return;
    }

    if (behavior->next.duration != -1) {
        this->nextBehaviorCountdown += deltaTime;

        if (this->nextBehaviorCountdown >= behavior->next.duration) {
            ChangeEntityBehavior(entity, behavior->next.nextBehaviorName);
        }
    }
}

// utility

std::shared_ptr<Behavior> BehaviorHandler::FindEntityBehavior(Entity* entity) const {
    const std::string_view state = entity->GetState();

    for (const auto& [name, behavior] : this->behaviorList) {
        if (name == state) {
            return behavior;
        }
    }

    std::cerr << "Entity assumed an invalid behavior state called " << state << "\n";
    throw;
}

void BehaviorHandler::ChangeEntityBehavior(Entity* entity, const std::string& nextBehaviorName) {
    entity->SetState(nextBehaviorName);
    this->nextBehaviorCountdown = 0.0f;
}
