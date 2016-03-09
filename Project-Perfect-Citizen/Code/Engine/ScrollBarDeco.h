#ifndef SCROLLBAR_DECO_H
#define SCROLLBAR_DECO_H

#include "WindowDecorator.h"
#include "../Game/buttonRenderComponent.h"
#include "../Game/mousePressButton.h"
#include "Entity.h"


namespace ppc {


class ScrollBarDecorator : public ppc::WindowDecorator {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    ScrollBarDecorator() = delete;

    ScrollBarDecorator(WindowInterface& win);

    ScrollBarDecorator(WindowInterface& win, sf::FloatRect& view);

    virtual ~ScrollBarDecorator();


  /////////////////////////////////////////////////////////////////////
  // Window Overrides
  /////////////////////////////////////////////////////////////////////

    sf::Vector2u getSize() override;

    void setSize(unsigned int x, unsigned int y) override;

    sf::FloatRect getBounds() override;

    void setPosition(float x, float y) override;

    void move(float dx, float dy) override;


  /////////////////////////////////////////////////////////////////////
  // View Manipulation
  /////////////////////////////////////////////////////////////////////

    void resetView(const sf::FloatRect& view);

    void setViewSize(const sf::Vector2f& size);

    void setViewCenter(const sf::Vector2f& center);

    void setViewPosition(const sf::Vector2f& center);

    void setBarSize(float barSize);

    void setBarSprite(const sf::Sprite& barSpr);

    void setButtonSprite(const sf::Sprite& buttonSpr);




protected:

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;


private:

  /////////////////////////////////////////////////////////////////////
  // Helper Functions
  /////////////////////////////////////////////////////////////////////

    void updateSliders();

    void updateView();


  /////////////////////////////////////////////////////////////////////
  // Private Variables
  /////////////////////////////////////////////////////////////////////

    float barSize_;

    sf::RectangleShape rectangleSprite_;

    sf::RectangleShape buttonSprite_;

    bool isHorizontal;


};


};


#endif  //End Scrollbar Deco
