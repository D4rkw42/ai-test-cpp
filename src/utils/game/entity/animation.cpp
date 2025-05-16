// handler de animações para entidades

#include "animation.hpp"

#include <iostream>

#include "utils/math/math.hpp"

AnimationHandler::AnimationHandler(void) {}

//

void AnimationHandler::RegisterAnimation(const GraphicsResources& graphicsResources, const std::string& animationID, const std::string& spritesheet, int numOfSprites, double duration, bool repeat) {
    this->list[animationID] = Animation { std::string(SPRITESHEET_PATH) + spritesheet, -1, numOfSprites, 0, duration, repeat, false };

    std::shared_ptr<Window> window = graphicsResources.window;
    std::shared_ptr<ImageHandler> imageHandler = graphicsResources.imageHandler;

    imageHandler->CreateImage(window, animationID, this->list[animationID].spritesheet.c_str());
    const std::shared_ptr<Image> image = imageHandler->GetImage(animationID);

    this->list[animationID].spriteWidth = image->width / numOfSprites;
}

void AnimationHandler::LoadAnimation(double deltaTime) {
    if (this->currID == "none") {
        return;
    }
    

    Animation& animation = this->list[currID];

    if (animation.inactive) {
        return;
    }

    // pula sprites
    double spriteStep = animation.duration / animation.numOfSprites;

    this->nextSpriteIn -= deltaTime;

    if (this->nextSpriteIn <= 0) {
        this->nextSpriteIn = spriteStep;
        animation.currSpriteID++;

        if (animation.currSpriteID == animation.numOfSprites) {
            animation.currSpriteID = 0;
        }
    }

    //

    this->nextAnimationIn -= deltaTime;

    if (this->nextAnimationIn < 0) {
        // garante que o tempo de animação não fique negativo, gerando tentativas de desenhar sprites inválidos
        this->nextAnimationIn = 0;

        if (animation.repeat) {
            this->nextAnimationIn = animation.duration;
            return;
        }

        animation.inactive = true;
    }
}

void AnimationHandler::DisplayAnimation(const GraphicsResources& graphicsResources, int x, int y, double scale, bool flip) {
    if (this->currID == "none") {
        return;
    }
    
    std::shared_ptr<Window> window = graphicsResources.window;
    std::shared_ptr<ImageHandler> imageHandler = graphicsResources.imageHandler;

    Animation& animation = this->list[this->currID];
    std::shared_ptr<Image> image = imageHandler->GetImage(this->currID);

    int spriteID = animation.currSpriteID;

    int cropX = animation.spriteWidth * spriteID;
    int cropY = 0;

    imageHandler->RenderImage(window, currID, x, y, cropX, cropY, animation.spriteWidth, image->height, scale, flip);
}

void AnimationHandler::StartAnimation(const std::string& animationID) {
    // não inicia uma nova animação se ela já estiver sendo executada
    if (this->currID == animationID) {
        return;
    }

    if (this->currID != "none") {
        this->list[this->currID].inactive = false;
        this->list[this->currID].currSpriteID = 0;
    }

    double spriteStep = this->list[animationID].duration / this->list[animationID].numOfSprites;

    this->nextAnimationIn = this->list[animationID].duration;
    this->nextSpriteIn = spriteStep;
    this->currID = animationID;
}

//

bool AnimationHandler::HasAnimationFinished(void) {
    if (this->currID == "none") {
        return false;
    }

    return this->list[this->currID].inactive;
}

void AnimationHandler::RestartAnimation(void) {
    if (this->currID == "none") {
        return;
    }

    this->nextAnimationIn = this->list[this->currID].duration;
    this->list[this->currID].inactive = false;
}

double AnimationHandler::GetAnimationTimePercent(void) {
    if (this->currID == "none") {
        return -1;
    }

    return 1.0f - (this->nextAnimationIn / this->list[this->currID].duration);
}
