// handler de animações para entidades

#pragma once

#include <string>
#include <unordered_map>

#include "system/resources.hpp"

// dados de animação
struct Animation {
    std::string spritesheet; // path para o spritesheet
    int spriteWidth; // largura do sprite
    int numOfSprites; // número de sprites
    double duration; // duração da animação em segundos
    bool repeat, inactive; // repetir? inativo?
};

// key-map para animações
typedef std::unordered_map<std::string, Animation> AnimationList; // <AnimationID, Animation>

// path para todas as amimações
constexpr const char* SPRITESHEET_PATH = "assets/sprites/mobs/";

class AnimationHandler {
    public:
        std::string currID = "none";

        AnimationHandler(void);

        // funções importantes
        void RegisterAnimation(const GraphicsResources& graphicsResources, const std::string& animationID, const std::string& spritesheet, int numOfSprites, double duration, bool repeat = true);

        void LoadAnimation(double deltaTime); // carrega as informações da animação -> usado em Update's
        void DisplayAnimation(const GraphicsResources& graphicsResources, int x, int y, double scale = 1.0f, bool flip = false); // renderiza a animação -> usado em Render's

        // utility

        // inicia uma nova animação
        void StartAnimation(const std::string& amimationID);

        // retorna por meios matemáticos qual o sprite que deve ser exibido naquele tempo de animaçãoo
        static int GetCurrentSpriteID(double duration, double countdown, int numOfSprites);

    private:
        AnimationList list;
        double nextAnimationIn;
};
