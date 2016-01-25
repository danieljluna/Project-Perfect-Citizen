#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H


namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Interface for all Window interactions.
/// @details Due to the relatively complicated Window hierarchy, this
///     class is needed to define the common interface between all 
///     classes in the hierarchy.
///////////////////////////////////////////////////////////////////////
class WindowInterface {
public:
    WindowInterface() = delete;

    virtual ~WindowInterface() {};

protected:


};


};      //End namespace



#endif  //End WINDOW_INTERFACE_H
