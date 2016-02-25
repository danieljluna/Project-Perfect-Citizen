#ifndef BORDER_DECORATOR_H
#define BORDER_DECORATOR_H

#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "WindowDecorator.h"
#include "DraggableInput.h"
#include "../Game/buttonRenderComponent.h"
#include "Entity.h"
#include "../Game/mousePressButton.h"

namespace ppc {


class BorderDecorator : public WindowDecorator {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    BorderDecorator() = delete;

    BorderDecorator(WindowInterface& win, 
					sf::Image& buttonSheet,
                    unsigned int majorBorder = 34, 
                    unsigned int minorBorder = 5);

    virtual ~BorderDecorator();


  /////////////////////////////////////////////////////////////////////
  // Decorated Functionality
  /////////////////////////////////////////////////////////////////////

    virtual sf::Vector2u getSize() override;

    virtual void setSize(unsigned int x, unsigned int y) override;

    virtual void setPosition(float x, float y) override;

    virtual void move(float x, float y) override;

    virtual sf::FloatRect getBounds() override;


protected:

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;


private:

    void updateBounds();

  /////////////////////////////////////////////////////////////////////
  // Private Variables 
  /////////////////////////////////////////////////////////////////////

    sf::Vector2u borderTopLeft_;
    sf::Vector2u borderBottomRight_;

    sf::RectangleShape borderShape_;

    DraggableInput draggableInput_;

	sf::Image& buttonSpriteSheet;
	sf::RectangleShape closeButtonArea_;

	buttonRenderComponent* closeRC_;
	mousePressButton* bIC_;
	Entity closeButton_;


};
    

};      //End namespace ppc


#endif  //BORDER_DECORATOR_H
