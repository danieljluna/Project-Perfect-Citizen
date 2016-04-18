#include "../Engine/debug.h"
#include "FloppyRenderComponent.hpp"
#include "../Engine/event.h"
#include <ostream>

using namespace ppc;


FloppyRenderComponent::FloppyRenderComponent(sf::Image& image) : floppyImage(image) {
    
    this->sprite = new sf::Sprite();
    this->texture = new sf::Texture();

    _willAnimate = false;
    
    xIndex = 0;
    yIndex = 0;
    rectSourceSprite = new sf::IntRect(xIndex*size, yIndex*size, size, size);

    /* Check that the file exists in the path */
    if (!texture->loadFromImage(image, sf::IntRect(0,0,5*size,3*size)))
        std::exit(-1);
    
    sprite->setTexture(*texture);
    sprite->setTextureRect(*rectSourceSprite);
    sprite->setPosition(0, 0);
    sprite->setScale(0.75f, 0.75f);
    setAnimationLoad();
}

FloppyRenderComponent::~FloppyRenderComponent() {
    delete texture;
    delete sprite;
    delete rectSourceSprite;
}

void FloppyRenderComponent::setAnimationLoad() {
    animation = 0;
    frameCount = 4;
    xIndex = 0;
    yIndex = 0;
    rectSourceSprite->left = xIndex*size;
    rectSourceSprite->top = yIndex*size;
    
    _willAnimate = true;
}

void FloppyRenderComponent::setAnimationHide() {
    animation = 1;
    frameCount = 4;
    xIndex = 4;
    yIndex = 0;
    rectSourceSprite->left = xIndex*size;
    rectSourceSprite->top = yIndex*size;
    
    _willAnimate = true;
}

void FloppyRenderComponent::renderPosition(sf::Vector2f pos) {
    sprite->setPosition(pos.x, pos.y);
}

void FloppyRenderComponent::setImageScale(float ScaleX, float ScaleY) {
    sprite->setScale(ScaleX, ScaleY);
}

void FloppyRenderComponent::setEmotion(int emote) {
    if (emote == 0) {
        // Happy Face
        rectSourceSprite->left = 0*size;
        rectSourceSprite->top = 1*size;
        sprite->setTextureRect(*rectSourceSprite);
    }
   
}


void FloppyRenderComponent::animate() {
    if (_willAnimate) {
        
        //Show Floppy With Emotion
        if (animation == 0) {
            if (rectSourceSprite->left == (frameCount * size)) {
                setEmotion(0);
                _willAnimate = false;
            } else {
                rectSourceSprite->left += size;
            }
        }
        //Hide Floppy
        else if (animation == 1) {
            if (rectSourceSprite->left == 0) {
                _willAnimate = false;
            } else {
                rectSourceSprite->left -= size;
            }
        }
        sprite->setTextureRect(*rectSourceSprite);
    }
}



void FloppyRenderComponent::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(*sprite, states);
}

void FloppyRenderComponent::recieveMessage(msgType code) {
}

void FloppyRenderComponent::recieveMessage(ppc::Event ev) {
   
}