#include "Window.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <cstddef>


using namespace ppc;


///////////////////////////////////////////////////////////////////////
// Constructors and Destructor
///////////////////////////////////////////////////////////////////////

Window::Window(unsigned int width, 
               unsigned int height, 
               sf::Color col) : 
            windowSpace_() {
    windowSpace_.create(width, height);
    backgroundColor_ = col;
    windowView_.reset(sf::FloatRect(0.0, 0.0, 
                                    float(width), float(height)));
    windowView_.setViewport(sf::FloatRect(0.f, 0.f, 1, 1));
}




Window::Window(const sf::Vector2u& size,
               sf::Color col) :
        Window(size.x, size.y, col) {}




Window::Window(const Window& other) :
    windowSpace_() {
    sf::Vector2u windowSize = other.windowSpace_.getSize();
    windowSpace_.create(windowSize.x, windowSize.y);
}




Window::~Window() {}




///////////////////////////////////////////////////////////////////////
// Step Functionality
///////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////
// Step Functionality
///////////////////////////////////////////////////////////////////////

void Window::addInputComponent(InputComponent* inputcmpnt) {
    if (inputcmpnt != nullptr) {
        inputcmpnts_.push_back(inputcmpnt);
    }
}




void Window::addRenderComponent(RenderComponent* rendercmpnt) {
    if (rendercmpnt != nullptr) {
        rendercmpnts_.push_back(rendercmpnt);
    }
}




void Window::addUpdateComponent(UpdateComponent* updatecmpnt) {
    if (updatecmpnt != nullptr) {
        updatecmpnts_.push_back(updatecmpnt);
    }
}




void Window::addEntity(Entity& entity) {
    //Stores the current index we're on
    size_t i = 0;
    //Stores the number of components we haven't found
    size_t toFind = entity.cmpntCount();

    //While we have more to find and more component* in the Entity:
    while ((toFind > 0) && (i < Entity::maxComponentCount)) {
        //Get the Component at the index
        Component* cmpnt = entity.getComponent(i);

        //If there is a Component at the point in question:
        if (cmpnt != nullptr) {
            //Test if it is an inputComponent
            if (dynamic_cast<InputComponent*>(cmpnt) != nullptr) {
                inputcmpnts_.push_back(dynamic_cast<InputComponent*>(cmpnt));
            //Test if it is an updateComponent
            } else if (dynamic_cast<UpdateComponent*>(cmpnt) != nullptr) {
                updatecmpnts_.push_back(dynamic_cast<UpdateComponent*>(cmpnt));
            } else if (dynamic_cast<RenderComponent*>(cmpnt) != nullptr) {
                rendercmpnts_.push_back(dynamic_cast<RenderComponent*>(cmpnt));
            }
        }

        //Search the next index
        ++i;
    }
}




///////////////////////////////////////////////////////////////////////
// Step Functionality
///////////////////////////////////////////////////////////////////////

void Window::update(sf::Time& deltaTime) {
    //Loop over all updateComponents
    for (UpdateComponent* c : updatecmpnts_) {
        c->update(deltaTime);
    }
}




void Window::registerInput(sf::Event& ev) {
    //TODO: Implement using InputHandler
}




void Window::refresh(sf::RenderStates states) {
    //Clear Window to Background Color
    windowSpace_.clear(backgroundColor_);

    //Apply the view
    windowSpace_.setView(windowView_);

    //Draws all objects in the window
    for (RenderComponent* c : rendercmpnts_) {
        windowSpace_.draw(*c, states);
    }

    windowSpace_.setView(windowSpace_.getDefaultView());

    windowSpace_.display();
}




void Window::draw(sf::RenderTarget& target,
                  sf::RenderStates states) const {
    //Create a sprite off of the windowSpace_
    sf::Sprite spr(windowSpace_.getTexture());

    states.transform *= getTransform();

    //Draw the sprite
    target.draw(spr, states);
}

