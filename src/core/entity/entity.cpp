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

void Entity::Init(const GraphicsResources& graphicsResources, AppGlobals& globals) {
    std::cerr << "Cannot use class<Entity> on its own" << "\n";
    throw;
}

void Entity::Update(AppGlobals& globals, double deltaTime) {
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

void Entity::Eliminate(void) {
    this->invalid = true;
}

double Entity::GetDistance(const std::shared_ptr<Entity>& e1, const std::shared_ptr<Entity>& e2) {
    return GetDistance(e1.get(), e2.get());
}

double Entity::GetDistance(Entity* e1, Entity* e2) {
    double distX = e1->pos.Get(0) - e2->pos.Get(0);
    double distY = e1->pos.Get(1) - e2->pos.Get(1);

    return std::sqrt(distX * distX + distY * distY);
}

// movement

void Entity::MoveTorwards(double vel, double angle) {
    double xCoef = std::cos(angle);
    double yCoef = std::sin(angle);

    double velX = vel * std::abs(xCoef);
    double velY = vel * std::abs(yCoef);

    velX *= (xCoef < 0)? -1 : 1;
    velY *= (yCoef < 0)? -1 : 1;

    this->vel.Set(0, velX);
    this->vel.Set(1, velY);
}
