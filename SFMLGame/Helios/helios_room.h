#ifndef HELIOS_ROOM_H
#define HELIOS_ROOM_H

#include <map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>


namespace Helios {

class BaseObj;

///////////////////////////////////////////////////////////////////////
/// @brief Describes a given space and the objects that exist within 
///     it in a way that facilitates consistent generation. Rooms are 
///     also responsible for calling update routines regularly,  
///     checking for collisions, and drawing objects.
///
///////////////////////////////////////////////////////////////////////
//TODO: Update comments for Room
class Room : public sf::Drawable {
public:

  //Constructors & Destructors:

    //Default Constructor
    Room();

    //No Copy Constructor
    Room(const Room& other) = delete;

    //No Move Constructor
    Room(Room&& other) = delete;

    //Constructs a Room of a Given Size
    Room(sf::Vector2u roomSize);

    //Destructor
    ~Room();


  //Operators:

    //No Copy Assignment Operator
    Room& operator=(const Room& other) = delete;

    //No Move Assignment Operator
    Room& operator=(Room&& other) = delete;


  //Step & Frame Functions:

    //Updates all objects
    void Update();


  //Object Management Functions:

    //Adds object to appropriate management lists
    void LinkObject(BaseObj *objPtr);

    //Removes object from all management lists
    void UnlinkObject(BaseObj *objPtr);
        

private:
    typedef std::multimap<unsigned int, BaseObj*> mmapIntObj;

  //Private Functions:
    
    //Redraws all objects
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    
    //Updates a linked object to the proper place in the updateList,
    //provided that object's priority does not match the exected 
    //priority.
    void UpdateObjectPriority(mmapIntObj::iterator objItor);
    
  //Private Fields:

    //Size of the space objects exist within (World Space)
    sf::Vector2u _size;

    //Update List
    mmapIntObj _updateList;

    //TODO: Collision Manager for Room Object

};


}   //namespace Helios

#endif  //HELIOS_ROOM_H
