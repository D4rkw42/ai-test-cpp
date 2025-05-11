// wrapper para gerenciar o comportamento de entidades

#pragma once

#include <memory>
#include <functional>
#include <unordered_map>

#include "core/entity/entity.hpp"

// definição de função para passar de estado pelo próprio comportamento
typedef std::function<void(const std::string&)> NextBehaviorCaller;

// definição da função de callback para um comportamento
typedef std::function<void(Entity*, double, const NextBehaviorCaller&)> BehaviorCallback; // entidade / deltatime / next

// definição da função que cria uma callback dinamicamente
typedef std::function<BehaviorCallback(void)> BehaviorCallbackCreator;

// representa os dados para o próximo comportamento
struct NextBehaviorData {
    std::string nextBehaviorName;
    double duration;
};

// definição de comportamento
struct Behavior {
    BehaviorCallback callback; // função de chamada
    NextBehaviorData next; // dados para o próximo comportamento
};

// Cria um objeto para um comportamento
inline std::shared_ptr<Behavior> CreateBehaviorObject(const BehaviorCallback& callback, const NextBehaviorData& nextBehaviorData) {
    std::shared_ptr<Behavior> behavior = std::make_shared<Behavior>();
    
    behavior->callback = callback;
    behavior->next = nextBehaviorData;

    return behavior;
}

// definição da lista de comportamentos
typedef std::unordered_map<std::string, std::shared_ptr<Behavior>> BehaviorList;

//

// para indicação dinâmica de mudança de comportamento
inline NextBehaviorData NextBehavior(const std::string name, double timeout = -1) {
    return NextBehaviorData { name, timeout };
}

// Gerencia os comportamentos
class BehaviorHandler {
    public:
        BehaviorHandler(void);
        ~BehaviorHandler(void);

        // criação dinâmica de comportamento
        void CreateBehavior(const std::string& name, const BehaviorCallback& callback, const NextBehaviorData& nextBehaviorData);
        void CreateBehavior(const std::string& name, const BehaviorCallback& callback);

        // executa o comportamento atual da entidade
        void LoadBehavior(Entity* entity, double deltaTime);

        // atualiza as informações para troca de comportamento automático, quando necessário
        void UpdateBehaviors(Entity* entity, double deltaTime);

    private:
        BehaviorList behaviorList;
        double nextBehaviorCountdown = 0.0f; // contagem para terminar o comportamento

        // utility

        // encontra o comportamento de uma entidade
        std::shared_ptr<Behavior> FindEntityBehavior(Entity* entity) const;

        // muda o comportamento de uma entidade a partir da mudança de seu estado
        void ChangeEntityBehavior(Entity* entity, const std::string& nextBehaviorName);
};
