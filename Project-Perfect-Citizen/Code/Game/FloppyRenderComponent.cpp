#include "../Engine/debug.h"
#include "FloppyRenderComponent.hpp"
#include "FloppyInputComponent.h"
#include "../Engine/event.h"
#include <ostream>

using namespace ppc;


FloppyRenderComponent::FloppyRenderComponent(sf::Image& image) : floppyImage(image) {
    
    this->sprite = new sf::Sprite();
    this->staticBox = new sf::Sprite();
    this->texture = new sf::Texture();
    
    
    
    /* Check that the file exists in the path */
    if (!texture->loadFromImage(image, sf::IntRect(0,0,2*size,5*size)))
        std::exit(-1);
    
    staticBox->setTexture(*texture);
    staticBox->setTextureRect(sf::IntRect(0,0,size,size));
    staticBox->setPosition(800, 32);
    staticBox->setScale(0.75f, 0.75f);
    
    
    xIndex = 0;
    yIndex = 1;
    rectSourceSprite = new sf::IntRect(xIndex*size, yIndex*size, size, size);
    
    
    sprite->setTexture(*texture);
    sprite->setTextureRect(*rectSourceSprite);
    sprite->setPosition(800, 35);
    sprite->setScale(0.75f, 0.75f);
    
    _willAnimate = false;
}

FloppyRenderComponent::~FloppyRenderComponent() {
    delete texture;
    delete sprite;
    delete staticBox;
    delete rectSourceSprite;
}

void FloppyRenderComponent::renderPosition(sf::Vector2f pos) {
    sprite->setPosition(pos.x, pos.y);
}

void FloppyRenderComponent::setImageScale(float ScaleX, float ScaleY) {
    sprite->setScale(ScaleX, ScaleY);
}

void FloppyRenderComponent::setEmotion(int emote) {
 
    if (emote == -1) {
        // No Face
        rectSourceSprite->left = 1*size;
        rectSourceSprite->top = 0*size;
    } else if (emote == 0) {
        // Default Face
        rectSourceSprite->left = 0*size;
        rectSourceSprite->top = 1*size;
    } else if (emote == 1) {
        // Angry Face
        rectSourceSprite->left = 0*size;
        rectSourceSprite->top = 2*size;
    } else if (emote == 2) {
        // Surprised
        rectSourceSprite->left = 0*size;
        rectSourceSprite->top = 3*size;
    } else if (emote == 3) {
        // Peek
        rectSourceSprite->left = 0*size;
        rectSourceSprite->top = 4*size;
    }
    
    sprite->setTextureRect(*rectSourceSprite);
    
}


void FloppyRenderComponent::animate() {
   /* if (emotion == -1) {
       // if (sprite->getPosition().y <= 32) {
         //   renderPosition({sprite->getPosition().x, sprite->getPosition().y+5});
        //} else {
            setEmotion(emotion);
            _willAnimate = false;
        //}
    } else {
        if (sprite->getPosition().y >= -35) {
            renderPosition({sprite->getPosition().x, sprite->getPosition().y-5});
        } else {
            setEmotion(emotion);
            _willAnimate = false;
        }
    }*/
    setEmotion(emotion);

   // sprite->setTextureRect(*rectSourceSprite);
}



void FloppyRenderComponent::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
	if (!_willAnimate) return;
    target.draw(*sprite, states);
    //target.draw(*staticBox, states);
}

void FloppyRenderComponent::recieveMessage(msgType code) {
}

void FloppyRenderComponent::recieveMessage(ppc::Event ev) {
    if (ev.type == Event::EventTypes::FloppyType) {
        unsigned int i = ev.floppy.sequence;
        unsigned int j = ev.floppy.frame;
        if (j == -1) emotion = -1;
        else emotion = FloppyInputComponent::floppyDictionary.at(i).at(j).second;
        std::cout << emotion << std::endl;
        setEmotion(emotion);
        _willAnimate = true;
    }
    
}