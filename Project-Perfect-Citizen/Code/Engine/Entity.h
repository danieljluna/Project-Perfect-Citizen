#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"


namespace ppc {

class Component;


//TODO: Finish Entity Interface
///////////////////////////////////////////////////////////////////////
/// @brief Uses a collection of Components to define a Entity
/// @details The Entity is a minimally intrusive class that holds 
///     together the real powerhouses: the Components. The only data
///     in Entity should be data accepted to be used by a vast majority
///     of Components.
///////////////////////////////////////////////////////////////////////
class Entity {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    //Constructor
    Entity();

    //Copy Constructor
    Entity(const Entity& other);

    //Destructor
    ~Entity();


private:

    //Holds the max amount of Components per Entity
    static const size_t maxComponentCount = 10;
    
    //Stores a collection of pointers to Components
    Component* components[maxComponentCount];


};


};      //End namespace ppc


#endif  //ENTITY_H
