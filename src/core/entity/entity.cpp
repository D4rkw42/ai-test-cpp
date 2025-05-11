// definições gerais de uma entidade

#include "entity.hpp"

#include <iostream>

#include <string_view>

#include "utils/game/entity/behavior-handler.hpp"

Entity::Entity(const std::string& type, const std::string& state, const Vec2& pos, const Vec2& vel) : type(type), pos(pos), vel(vel) {
    this->behaviors = new BehaviorHandler;

    this->state = std::make_shared<std::string>();
    this->prevState = std::make_shared<std::string>();

    *this->prevState = "none";

    SetState(state);
}

Entity::Entity(void) {}

//

Entity::~Entity(void) {
    delete this->behaviors;
}

//

void Entity::Init(const GraphicsResources& graphicsResources) {
    std::cerr << "Cannot use class<Entity> on its own" << "\n";
    throw;
}

void Entity::Update(double deltaTime) {
    std::cerr << "Cannot use class<Entity> on its own" << "\n";
    throw;
}

void Entity::Render(const GraphicsResources& graphicsResources) {
    std::cerr << "Cannot use class<Entity> on its own" << "\n";
    throw;
}

// utility

void Entity::SetState(const std::string& state) {
    *this->prevState = *this->state;
    *this->state = state;
}

const std::string_view Entity::GetState(void) const {
    return std::string_view(this->state->c_str());
}

const std::string_view Entity::GetPrevState(void) const {
    return std::string_view(this->prevState->c_str());
}
