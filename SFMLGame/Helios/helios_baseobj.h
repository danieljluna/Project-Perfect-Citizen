#ifndef HELIOS_BASEOBJ_H
#define HELIOS_BASEOBJ_H

#include <vector>

#include <SFML/Graphics/Drawable.hpp>

namespace Helios {

class Room;


///////////////////////////////////////////////////////////////////////
/// @brief An abstract class representing an interface all objects 
///     should adhere to.
/// @details BaseObj is merely defines interface for all objects. Thus,
///     all objects should have an Update function, which is inteded to
///     be called on the object for each game step.\n
///     All objects are also sf::Drawables, and will only draw if they
///     are visible. Specify how to draw derived classes with the 
///     virtual function render in order to maintain visible 
///     functionality.\n
///     Objects are also designed to be managed by the Helios::Room 
///     class. For this reason, they may be set as active in a room
///     using the Activate function. This will inform both parties that
///     the Helios::Room in question is responsible for managing 
///     Update and draw function calls as well as interactions between
///     objects in the Helios::Room.\n
///     The priority of any object can changes the priority of this 
///     object's draw and Update functions with respect to the other
///     objects handled by the same Helios::Room.\n
///
///
///////////////////////////////////////////////////////////////////////
class BaseObj : public sf::Drawable {
    friend Room;

public:

    //No Universal Copy Constructor
    BaseObj(const BaseObj& other) = delete;

    //No Universal Move Constructor
    BaseObj(BaseObj&& other) = delete;

    //Virtual Destructor
    virtual ~BaseObj();


  /////////////////////////////////////////////////////////////////////
  //  Operators:
  /////////////////////////////////////////////////////////////////////
    
    //No Universal Copy Assignment Operator
    BaseObj& operator=(const BaseObj& other) = delete;

    //No Universal Move Assignment Operator
    BaseObj& operator=(BaseObj&& other) = delete;


  /////////////////////////////////////////////////////////////////////
  //  Accsessor Functions:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns a pointer to the room this object is active in,
    /// provided it is active. If this object is not active, it will
    /// return nullptr.
    ///
    /// @return Room* indicating room this object is active in
    /// 
    ///////////////////////////////////////////////////////////////////
    Room* get_room() const;

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the priority for this object in the update 
    /// cycle.
    ///
    /// @return signed int indicating object priority.
    /// 
    /// @see set_priority()
    /// 
    ///////////////////////////////////////////////////////////////////
    signed int get_priority() const;

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns whether the object is flagged to be drawable.
    /// 
    /// @return bool indicating draw status.
    /// 
    /// @see set_visible()
    /// 
    ///////////////////////////////////////////////////////////////////
    bool is_visible() const;

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns whether the BaseObject is active. Active objects
    /// are linked to a Room that keeps maintains Update() calls, 
    /// collision checking, and drawing.
    /// 
    /// @return bool indicating active status.
    /// 
    /// @see Activate(Room &roomHandle), Deactivate()
    /// 
    ///////////////////////////////////////////////////////////////////
    bool is_active() const;


  /////////////////////////////////////////////////////////////////////
  //  Mutator Functions:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Links object to a room and thus to that room's update 
    /// cycle / collision checks, etc. Does nothing if the object is
    /// already active in a room. Nothing happens if the roomHandle is
    /// nullptr.
    /// 
    /// @see is_active(), Deactivate(Room &roomHandle)
    /// 
    ///////////////////////////////////////////////////////////////////
    void Activate(Room &roomHandle);

    ///////////////////////////////////////////////////////////////////
    /// @brief Disconnects and object from its associated room - if 
    /// any - preventing it from engaging in regular updates, collision 
    /// checks and other room dependant interactions.
    /// 
    /// @see active(), Activate(Room &roomHandle)
    /// 
    ///////////////////////////////////////////////////////////////////
    void Deactivate();

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the priority of this object's update. This priority
    /// will be updated in the current Room before the next update.
    /// 
    /// @see get_priority()
    /// 
    ///////////////////////////////////////////////////////////////////
    void set_priority(const unsigned int prior);

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets a property determining whether or not this object
    /// can be drawn via the public Draw function.
    /// 
    /// @see visible()
    /// 
    ///////////////////////////////////////////////////////////////////
    void set_visible(const bool vis);


  /////////////////////////////////////////////////////////////////////
  //  Step and Frame Functions:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Function called by the Room this object is active in to
    /// update this object for the next frame.
    ///
    ///////////////////////////////////////////////////////////////////
    virtual void Update() = 0;


protected:

  /////////////////////////////////////////////////////////////////////
  //  Proctected Methods
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Default Constructor. 
    /// @details Creates an object that is inactive and invisible, with
    ///     the given priority (default zero).
    ///
    ///////////////////////////////////////////////////////////////////
    BaseObj(const unsigned int priority = 0);
    
    ///////////////////////////////////////////////////////////////////
    /// @brief Overwrite this function to define how this object 
    ///     should be rendered on a render target. This definition will
    ///     likely vary radically for each derived class.
    ///////////////////////////////////////////////////////////////////
    virtual void render(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    

  /////////////////////////////////////////////////////////////////////
  //  Proctected Data
  /////////////////////////////////////////////////////////////////////

    //Denotes the priority of the object's update funciton relative to
    //other objects. Default is zero.
    signed int _priority;

    //A bool regulating whether or not this object should be drawn.
    bool _visible;


private:

  /////////////////////////////////////////////////////////////////////
  //  Private Functions
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Draws the object to the target as programmed in render()
    /// after making the appropriate visiblity checks. Also allows the 
    /// typical SFML draw call syntax of RenderTarget.draw(BaseObj).
    ///
    /// @note While this function *is* an inherited virtual function,
    /// it is assumed this function will not be overwritten in child
    /// classes. Doing so may ruin visible functionality. Instead edit
    /// the virtual function render().
    ///
    ///////////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;


  /////////////////////////////////////////////////////////////////////
  //  Private Data
  /////////////////////////////////////////////////////////////////////

    //Pointer the the room this object resides in.
    //If it equals nullptr, the object is inactive.
    Room* _roomHandle;


};  //End BaseObj Declaration------------------------------------------




}   //namespace Helios-------------------------------------------------

#endif  //HELIOS_BASEOBJ_H
