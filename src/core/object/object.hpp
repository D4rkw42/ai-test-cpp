// definição geral para objetos polimórticos

#pragma once

#include <memory>

#include "system/resources.hpp"

class Object {
    public:
        int x, y, size;

        Object(int x, int y, int size);
        ~Object(void);

        virtual void Init(const GraphicsResources& graphicsResources);
        virtual void Render(const GraphicsResources& graphicsResources);
};

// declaração para lists de objetos
template <int objectListLimit>
using ObjectList = std::array<std::shared_ptr<Object>, objectListLimit>;

// criação dinâmica de objetos
template <class ObjectType>
std::shared_ptr<Object> CreateObject(int x, int y, int size) {
    std::shared_ptr<ObjectType> object = std::make_shared<ObjectType>(x, y, size);
    return std::dynamic_pointer_cast<Object>(object);
}

template <int objectListLimit>
void SaveObject(ObjectList<objectListLimit>& list, std::shared_ptr<Object> object) {
    for (int i = 0; i < objectListLimit; ++i) {
        if (list[i] == nullptr) {
            list[i] = object;
            return;
        }
    }
}

// destroi todos os objetos de uma lista
template <int objectListLimit>
void DestroyAllObjects(const ObjectList<objectListLimit>& list) {
    for (std::shared_ptr<Object>& object : list) {
        object = nullptr;
    }
}
