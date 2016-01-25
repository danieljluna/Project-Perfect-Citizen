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


protected:

    WindowInterface* getDecoTarget() { return windowHandle_; };


private:

    //A Pointer to the Window this decorates
    WindowInterface* windowHandle_;


};


};      //End namespace ppc


#endif  //WINDOW_DECORATOR_H
