#ifndef HELIOS_MAIN_H
#define HELIOS_MAIN

#include <list>

#include <SFML/Graphics.hpp>

namespace Helios {
class Room;
class BaseObj;

//TODO: Add BaseObj 'dynamic' functionality

///////////////////////////////////////////////////////////////////////
/// \breif An abstract parent class providing the basis for packaging 
///     sprite with the appropriate logic functions all objects in the
///     room need.
///
///////////////////////////////////////////////////////////////////////
class BaseObj {
  public:

  /////////////////////////////////////////////////////////////////////
  /// Constructors & Destructors:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// \breif Default Constructor
    ///
    /// Creates an object that is inactive, invisible, and has no 
    /// sprite.
    ///
    ///////////////////////////////////////////////////////////////////
    BaseObj();
    
    //No Universal Copy Constructor
    BaseObj(const BaseObj& other) = delete;

    //No Universal Move Constructor
    BaseObj(BaseObj&& other) = delete;
    
    ///////////////////////////////////////////////////////////////////
    /// \breif Default Destructor
    /// 
    /// Simply destroys all data linked to the BaseObject.
    /// 
    ///////////////////////////////////////////////////////////////////
    ~BaseObj();


  /////////////////////////////////////////////////////////////////////
  /// Operators:
  /////////////////////////////////////////////////////////////////////

    //No Universal Copy Assignment Operator
    BaseObj& operator=(const BaseObj& other) = delete;

    //No Universal Move Assignment Operator
    BaseObj& operator=(BaseObj&& other) = delete;


  /////////////////////////////////////////////////////////////////////
  /// Accsessor Functions:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// \breif Returns whether the object is flagged to be drawn by the
    /// room this object is active in. 
    ///
    /// \note An inactive object that is visible will not be drawn 
    /// since there is no room responsible for drawing it!
    /// 
    /// \return bool indicating draw status.
    /// 
    /// \see set_visible()
    /// 
    ///////////////////////////////////////////////////////////////////
    bool visible() const;

    ///////////////////////////////////////////////////////////////////
    /// \breif Returns whether the BaseObject is active. Active objects
    /// are linked to a Room that keeps maintains Update() calls, 
    /// collision checking, and drawing.
    /// 
    /// \return bool indicating active status.
    /// 
    /// \see Activate(Room &roomHandle), Deactivate()
    /// 
    ///////////////////////////////////////////////////////////////////
    bool active() const;


  /////////////////////////////////////////////////////////////////////
  /// Mutator Functions:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// \breif Sets a property determining whether or not this object
    /// will be drawn by the room this object is active in. The object
    /// will only be drawn if this property is set to true.
    ///
    /// \note An inactive object that is visible will not be drawn 
    /// since there is no room responsible for drawing it!
    /// 
    /// \see visible()
    /// 
    ///////////////////////////////////////////////////////////////////
    void set_visible(const bool vis);

    ///////////////////////////////////////////////////////////////////
    /// \breif Links object to a room and thus to that room's update 
    /// cycle / collision checks, etc. Does nothing if the object is
    /// already active in a room.
    /// 
    /// \see active(), Deactivate(Room &roomHandle)
    /// 
    ///////////////////////////////////////////////////////////////////
    void Activate(Room &roomHandle);

    ///////////////////////////////////////////////////////////////////
    /// \breif Disconnects and object from its associated room - if any 
    /// - preventing it from engaging in regular updates, collision 
    /// checks and other room dependant interactions.
    /// 
    /// \see active(), Activate(Room &roomHandle)
    /// 
    ///////////////////////////////////////////////////////////////////
    void Deactivate();

  /////////////////////////////////////////////////////////////////////
  /// Step Functions:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// \breif Function called by the Room this object is active in to
    /// update this object for the next frame.
    ///
    ///////////////////////////////////////////////////////////////////
    virtual unsigned int Update() = 0;

  
  protected:

  
      
  /////////////////////////////////////////////////////////////////////
  /// Member Data
  /////////////////////////////////////////////////////////////////////

    //Pointer the the room this object resides in.
    //If it equals nullptr, the object is inactive.
    Room* _roomHandle;

    //Contains the visual representation of the object
    sf::Sprite _sprite;

    //Override to prevent object from being drawn when false.
    bool _visible;

    //Denotes whether this object ceases to exist when the room changes
    //(false), or whether it carries into the next room (true).
    bool _persistent;
};




//TODO: Add Room 'Object Management' functionality

///////////////////////////////////////////////////////////////////////
/// \breif Describes a given space and the objects that exist within 
/// it in a way that facilitates consistent generation. Rooms are 
/// also responsible for calling update routines regularly, checking 
/// for collisions, and drawing objects.
///
///////////////////////////////////////////////////////////////////////
class Room {
  public:

  //Constructors & Destructors:

    //Default Constructor
    Room();

    //Copy Constructor
    Room(const Room& other);

    //Move Constructor
    Room(Room&& other);

    //Destructor
    ~Room();


  //Operators:

    //Copy Assignment Operator
    Room& operator=(const Room& other);

    //Move Assignment Operator
    Room& operator=(Room&& other);


  //Step & Frame Functions:

    //Updates all objects
    unsigned int update();

    //Redraws all objects
    unsigned int draw();


  //Object Management Functions:

    //Adds object to appropriate management lists
    void LinkObject(BaseObj &);
        

  private:

  //Private Fields:

    //Size of the space objects exist within
    sf::Vector2f _size;

    //Object Container
    std::list<BaseObj> _objList;

};

}   //namespace Helios

#endif  //HELIOS_MAIN_H
