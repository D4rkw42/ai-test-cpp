// definição geral para objetos polimórficos

#include "object.hpp"

#include <iostream>

Object::Object(const std::string& type, int x, int y, int size) : type(type), x(x), y(y), size(size) {}
Object::~Object(void) {}

void Object::Render(const GraphicsResources& graphicsResources) {
    std::cerr << "Cannot use Class<Object> on its own" << "\n";
    throw;
}

void Object::Init(const GraphicsResources& graphicsResources) {
    std::cerr << "Cannot use Class<Object> on its own" << "\n";
    throw;
}
