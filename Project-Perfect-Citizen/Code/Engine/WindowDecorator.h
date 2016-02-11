#ifndef WINDOW_DECORATOR_H
#define WINDOW_DECORATOR_H

#include "WindowInterface.h"

namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Decorator for any Window.
/// @author Daniel Luna
/// @details Any Decorator for the Window hierarchy needs to inherit 
///     this class. Decorators are designed to add functionality to a
///     Window. If DecoratorA decorates a WindowB, then DecoratorA will
///     get used as a handle to WindowB. When a member function is 
///     called, DecoratorA.fn(), it does extra leg-work specific to
///     the decorator, if any, then calles WindowB.fn(). Decorators can
///     stack.
/// @note Many functions are not documented in the .h file as Doxygen
///     automatically take the docs from parent classes when none are
///     provided.
///////////////////////////////////////////////////////////////////////
class WindowDecorator : public WindowInterface {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors and Destructors
  /////////////////////////////////////////////////////////////////////

    //No Default Destructor
    WindowDecorator() = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Attaches this Decorator to a Window
    ///////////////////////////////////////////////////////////////////
    WindowDecorator(WindowInterface& window);

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor
    /// @details Destroys the decorated Window.
    ///////////////////////////////////////////////////////////////////
    virtual ~WindowDecorator();


    // Space Setters

    virtual void setSize(unsigned int width, unsigned int height) override;

    // Transformation Setters

    virtual void setPosition(float x, float y) override;
    virtual void move(float dx, float dy) override;
    virtual void setScale(float xscale, float yscale) override;
    virtual void scale(float xscale, float yscale) override;

    //Transformation Getters

    virtual sf::Vector2f getPosition() const override;
    virtual sf::Vector2f getScale() const override;

    //Component Manipulation

	virtual void addInputComponent(InputComponent* inputcmpnt) override;
	virtual void addRenderComponent(RenderComponent* rendercmpnt) override;
	virtual void addUpdateComponent(UpdateComponent* updatecmpnt) override;
	virtual void addEntity(Entity& entity) override;

    //Game Loop Functionality

	virtual void update(sf::Time& deltaTime) override;
	virtual void registerInput(sf::Event&) override;
	virtual void refresh(sf::RenderStates states = sf::RenderStates()) override;

protected:

    WindowInterface* getDecoTarget() const { return windowHandle_; };

	virtual void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;

private:

    //A Pointer to the Window this decorates
    WindowInterface* windowHandle_;


};


};      //End namespace ppc


#endif  //WINDOW_DECORATOR_H
