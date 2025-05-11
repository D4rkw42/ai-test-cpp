// handler de animações para entidades

#include "animation.hpp"

#include <iostream>

#include "utils/math/math.hpp"

AnimationHandler::AnimationHandler(void) {}

//

void AnimationHandler::RegisterAnimation(const GraphicsResources& graphicsResources, const std::string& animationID, const std::string& spritesheet, int numOfSprites, double duration, bool repeat) {
    this->list[animationID] = Animation { std::string(SPRITESHEET_PATH) + spritesheet, -1, numOfSprites, duration, repeat, false };

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

    this->nextAnimationIn -= deltaTime;

    if (this->nextAnimationIn <= 0) {
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

    int spriteID = AnimationHandler::GetCurrentSpriteID(animation.duration, this->nextAnimationIn, animation.numOfSprites);

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
    }

    this->nextAnimationIn = this->list[animationID].duration;
    this->currID = animationID;
}

//

bool AnimationHandler::HasAnimationFinished(void) {
    if (this->currID == "none") {
        return false;
    }

    return this->list[this->currID].inactive;
}

double AnimationHandler::GetAnimationTimePercent(void) {
    if (this->currID == "none") {
        return -1;
    }

    return 1.0f - (this->nextAnimationIn / this->list[this->currID].duration);
}

//

int AnimationHandler::GetCurrentSpriteID(double duration, double countdown, int numOfSprites) {
    return static_cast<int>(map(countdown / duration, 0, 1, numOfSprites, 0));
}
