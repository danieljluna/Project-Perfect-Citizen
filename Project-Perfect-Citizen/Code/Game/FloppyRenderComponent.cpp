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
    setAnimationPeek();
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

void FloppyRenderComponent::setAnimationPeek() {
    animation = 2;
    frameCount = 4;
    xIndex = 2;
    yIndex = 2;
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
    switch (emote) {
        case 0:
            // Happy Face
            rectSourceSprite->left = 0*size;
            rectSourceSprite->top = 1*size;
            break;
        case 1:
            // Angry Face
            rectSourceSprite->left = 2*size;
            rectSourceSprite->top = 1*size;
        case 2:
            // Surprised
            rectSourceSprite->left = 0*size;
            rectSourceSprite->top = 2*size;
        case 3:
            // Resting
            rectSourceSprite->left = 0*size;
            rectSourceSprite->top = 0*size;
        default:
            break;
    }

    sprite->setTextureRect(*rectSourceSprite);
   
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
        
        //Peek Floppy
        else if (animation == 2) {
            if (rectSourceSprite->left == frameCount * size) {
               // _willAnimate = false;
                animation += 1;
            } else {
                rectSourceSprite->left += size;
            }
        } else if (animation == 3) {
            if (rectSourceSprite->left == 2*size) {
                setEmotion(3);
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
   /* switch (ev.type) {
        case Event::EventTypes::EmotionType:
            if (ev.emotions.isDefault) {
                setEmotion(0);
            }
            if (ev.emotions.isAngry){
                setEmotion(1);
            }
            if (ev.emotions.isSurprised){
                setEmotion(2);
            }
            if (ev.emotions.isPeeked){
                setAnimationPeek();
            }
            if (ev.emotions.isHidden){
                setAnimationHidden();
            }
            break;
        default:
            break;
    }*/

}