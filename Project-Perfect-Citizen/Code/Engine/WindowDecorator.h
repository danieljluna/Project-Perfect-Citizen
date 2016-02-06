#ifndef WINDOW_DECORATOR_H
#define WINDOW_DECORATOR_H

#include "WindowInterface.h"

namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Decorator for any Window.
/// @details Any Decorator for the Window hierarchy needs to inherit 
///     this class. Decorators are designed to add functionality to a
///     Window. If DecoratorA decorates a WindowB, then DecoratorA will
///     get used as a handle to WindowB. When a member function is 
///     called, DecoratorA.fn(), it does extra leg-work specific to
///     the decorator, if any, then calles WindowB.fn(). Decorators can
///     stack.
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
    WindowDecorator(WindowInterface& windowPtr);

    virtual ~WindowDecorator();


	virtual void addInputComponent(InputComponent* inputcmpnt);
	virtual void addRenderComponent(RenderComponent* rendercmpnt);
	virtual void addUpdateComponent(UpdateComponent* updatecmpnt);
	virtual void addEntity(Entity& entity);

	virtual void update(sf::Time& deltaTime);
	virtual void registerInput(sf::Event&);
	virtual void refresh(sf::RenderStates states = sf::RenderStates());

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
