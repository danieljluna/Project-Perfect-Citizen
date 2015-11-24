#ifndef HELIOS_OBJECT_COMPONENT_H
#define HELIOS_OBJECT_COMPONENT_H

namespace hls {


class Component {
    virtual ~Component();
    virtual void recieve(int message) = 0;
    virtual void update();
};

///////////////////////////////////////////////////////////////////////
/// @brief Interface for Input Components, which are responsible for
///     reacting to user input.
///////////////////////////////////////////////////////////////////////
class InputComponent : public Component {

};

///////////////////////////////////////////////////////////////////////
/// @brief Interface for Dynamic Components, which are responsible for
///     handling object interactions with the world given the input.
///////////////////////////////////////////////////////////////////////
class DynamicComponent {

};

///////////////////////////////////////////////////////////////////////
/// @brief Interface for Render Components, which are responsible for 
///     handling object representation.
///////////////////////////////////////////////////////////////////////
class RenderComponent {

};


};   //End namespace hls


#endif  //End HELIOS_OBJECT_COMPONENT_H
