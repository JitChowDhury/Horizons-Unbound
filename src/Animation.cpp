#include "Animation.h"


Animation::Animation(sf::Sprite& targetSprite, float frameDuration)
    : sprite(targetSprite), frameTime(frameDuration), elapsedTime(0.f), currentFrame(0) {
}

void Animation::AddFrame(const sf::IntRect& frame) {
    frames.push_back(frame);
}

void Animation::Update(float deltaTime) {
    if (frames.empty()) return;

    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime) {
        elapsedTime = 0.f;
        currentFrame = (currentFrame + 1) % frames.size();
        sprite.setTextureRect(frames[currentFrame]);
    }
}

void Animation::Reset() {
    elapsedTime = 0.f;
    currentFrame = 0;

    if (!frames.empty()) {
        sprite.setTextureRect(frames[0]);
    }
}