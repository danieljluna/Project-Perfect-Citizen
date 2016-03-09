#ifndef SCROLLBAR_DECO_H
#define SCROLLBAR_DECO_H

#include "WindowDecorator.h"
#include "../Game/buttonRenderComponent.h"
#include "../Game/mousePressButton.h"
#include "DraggableInput.h"
#include "Entity.h"


namespace ppc {


class ScrollBarDecorator : public ppc::WindowDecorator {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    ScrollBarDecorator() = delete;

    ScrollBarDecorator(WindowInterface& win);

    ScrollBarDecorator(WindowInterface& win, const sf::View& view);

    virtual ~ScrollBarDecorator();


  /////////////////////////////////////////////////////////////////////
  // Window Overrides
  /////////////////////////////////////////////////////////////////////

    sf::Vector2u getSize() const override;

    void setSize(unsigned int x, unsigned int y) override;

    sf::FloatRect getBounds() const override;

    void setPosition(float x, float y) override;

    void move(float dx, float dy) override;

    void setView(const sf::View& view) override;

    

  /////////////////////////////////////////////////////////////////////
  // View Manipulation
  /////////////////////////////////////////////////////////////////////

    void setBarSize(float barSize);

    void setBarSprite(const sf::Sprite& barSpr);

    void setBarBkgrndSprite(const sf::Sprite& bkgrndSpr);

    void setButtonSprite(const sf::Sprite& buttonSpr);




protected:

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;


private:

  /////////////////////////////////////////////////////////////////////
  // Helper Functions
  /////////////////////////////////////////////////////////////////////

    void repositionSliders();

    void updateInput();
    
    void updateSliders();

    void updateView();

    void initialize();


  /////////////////////////////////////////////////////////////////////
  // Private Variables
  /////////////////////////////////////////////////////////////////////

    float barSize_;

    //Array of ScrollBar Rectangles
    sf::RectangleShape scrollBars_[2];
    //Stores the input Component that allows the Window to be dragged 
    //  via the BorderDecorator.
    DraggableInput* draggableInputs_[2];
    //Array of ScrollBar Backgrounds
    sf::RectangleShape scrollBackgrounds_[2];
    


    //Array of buttonRenderComponents
    buttonRenderComponent* buttonRenders_[4];
    //Array of buttonInputComponents
    mousePressButton* buttonInputs_[4];
    //Array of button Entities
    Entity buttonEntities_[4];


};


};


#endif  //End Scrollbar Deco
