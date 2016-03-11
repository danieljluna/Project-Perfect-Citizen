#ifndef SCROLLBAR_DECO_H
#define SCROLLBAR_DECO_H

#include "WindowDecorator.h"
#include "Entity.h"
#include "FreeFunctionObserver.h"


namespace ppc {

class DraggableInput;
class mousePressButton;
class buttonRenderComponent;


class ScrollBarDecorator : public ppc::WindowDecorator {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    ScrollBarDecorator() = delete;

    ScrollBarDecorator(WindowInterface& win, sf::Image& img);

    ScrollBarDecorator(WindowInterface& win, sf::Image& img, 
                       const sf::View& view);

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

    void updateButtons();

    void updateDraggable();
    
    void updateSliders();

    void updateView();

    void initialize(sf::Image img);

    friend bool onSliderDrag(ScrollBarDecorator*, sf::Event&);
    friend bool onButtonUp(ScrollBarDecorator*, sf::Event&);
    friend bool onButtonDown(ScrollBarDecorator*, sf::Event&);
    friend bool onButtonLeft(ScrollBarDecorator*, sf::Event&);
    friend bool onButtonRight(ScrollBarDecorator*, sf::Event&);


  /////////////////////////////////////////////////////////////////////
  // Private Variables
  /////////////////////////////////////////////////////////////////////

    float barSize_ = 20.0f;

    //Array of ScrollBar Rectangles
    sf::RectangleShape scrollBars_[2];
    //Stores the input Component that allows the Window to be dragged 
    //  via the BorderDecorator.
    DraggableInput* draggableInputs_[2];
    //Array of ScrollBar Backgrounds
    sf::RectangleShape scrollBackgrounds_[2];
    //Function Observers for ScrollBars
    FreeFunctionObserver<ScrollBarDecorator> *obsvrs_[6];
    


    //Array of buttonRenderComponents
    buttonRenderComponent* buttonRenders_[4];
    //Array of buttonInputComponents
    mousePressButton* buttonInputs_[4];
    //Array of button Entities
    Entity buttonEntities_[4];


};



bool onSliderDrag(ScrollBarDecorator*, sf::Event&);

bool onButtonUp(ScrollBarDecorator*, sf::Event&);

bool onButtonDown(ScrollBarDecorator*, sf::Event&);

bool onButtonLeft(ScrollBarDecorator*, sf::Event&);

bool onButtonRight(ScrollBarDecorator*, sf::Event&);









};


#endif  //End Scrollbar Deco
