#ifndef WINDOW_DECORATOR_H
#define WINDOW_DECORATOR_H

#include "Window.h"

namespace ppc {


class WindowDecorator : public Window {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors and Destructors
  /////////////////////////////////////////////////////////////////////

    //No Default Destructor
    WindowDecorator() = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Attaches this Decorator to a Window
    ///////////////////////////////////////////////////////////////////
    WindowDecorator(Window& windowPtr);

    virtual ~WindowDecorator();


protected:

    Window* getDecoTarget() { return windowHandle_; };


private:

    //A Pointer to the Window this decorates
    Window* windowHandle_;


};


};      //End namespace ppc


#endif  //WINDOW_DECORATOR_H
