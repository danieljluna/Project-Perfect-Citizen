#ifndef BORDER_DECORATOR_H
#define BORDER_DECORATOR_H

#include "WindowDecorator.h"

namespace ppc {


class BorderDecorator : public WindowDecorator {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    BorderDecorator() = delete;

    BorderDecorator(WindowInterface& win, 
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


protected:

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;


private:

  /////////////////////////////////////////////////////////////////////
  // Private Variables 
  /////////////////////////////////////////////////////////////////////

    sf::Vector2u borderTopLeft_;
    sf::Vector2u borderBottomRight_;

    sf::RectangleShape borderShape_;

    bool isBeingDragged_;


};
    

};      //End namespace ppc


#endif  //BORDER_DECORATOR_H
