// gerencia a geração do ambiente

#pragma once

#include <string>

// configurações
constexpr int OBJECT_SIZE = 10; // tamanho do objeto
constexpr int MIN_TREE_NEAR_DISTANCE = 30; // distância mínima para árvores

class AmbientController {
    public:
        // Gera o ambiente
        void GenerateAmbient(void);

        // Renderiza o ambiente
        void RenderAmbient(void);

    private:
        // Verifica se existe um objeto próximo
        bool FindObjectNear(const std::string& type, double x, double y, double reference);
};
