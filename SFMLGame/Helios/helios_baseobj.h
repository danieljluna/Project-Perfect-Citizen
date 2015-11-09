#ifndef HELIOS_BASEOBJ_H
#define HELIOS_BASEOBJ_H

#include <SFML/Graphics/Drawable.hpp>

class RenderStates;
class RenderTarget;
class Sprite;

namespace helios {

class Room;


///////////////////////////////////////////////////////////////////////
/// @brief An abstract class representing an interface all objects 
///     should adhere to.
/// @details BaseObj is merely defines interface for all objects. Thus,
///     all objects should have an Update function, which is inteded to
///     be called on the object for each game step.\n\n
///     All objects are also sf::Drawables, and will only draw if they
///     are visible. Specify how to draw derived classes with the 
///     virtual function render in order to maintain visible 
///     functionality.\n\n
///     Objects are also designed to be managed by the Room class. For 
///     this reason, they may be set as active in a room using the 
///     Activate function. This will inform both parties that the Room 
///     in question is responsible for managing Update and draw 
///     function calls as well as interactions between objects in the 
///     Room.\n
///////////////////////////////////////////////////////////////////////
class BaseObj : public sf::Drawable {
    friend Room;

public:

    ///////////////////////////////////////////////////////////////////
    /// @brief Deleted Copy Constructor
    ///////////////////////////////////////////////////////////////////
    BaseObj(const BaseObj& other) = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Deleted Move Constructor
    ///////////////////////////////////////////////////////////////////
    BaseObj(BaseObj&& other) = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor
    ///////////////////////////////////////////////////////////////////
    virtual ~BaseObj();


  /////////////////////////////////////////////////////////////////////
  // Operators:
  /////////////////////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////////////////
    /// @brief Deleted Copy Assignment Operator
    ///////////////////////////////////////////////////////////////////
    BaseObj& operator=(const BaseObj& other) = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Deleted Move Assignment Operator
    ///////////////////////////////////////////////////////////////////
    BaseObj& operator=(BaseObj&& other) = delete;


  /////////////////////////////////////////////////////////////////////
  //  Accsessor Functions:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns a pointer to the room this object is active in.
    /// @details Inactive objects return nullptr.
    ///
    /// @return Room* handle
    ///////////////////////////////////////////////////////////////////
    Room* get_room() const;

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the current priority of this object.
    /// @details The object's priority represents how early in the 
    ///     update cycle this object's Update() and draw() calls should
    ///     be made. Given two objects, the object with the higher
    ///     priority should be updated and drawn before the other.
    ///
    /// @return signed int priority.
    /// 
    /// @see set_priority(const signed int)
    ///////////////////////////////////////////////////////////////////
    signed int get_priority() const;

    ///////////////////////////////////////////////////////////////////
    /// @brief Checks if the object is visible.
    /// @details If an object is not visible, then calls to draw that
    ///     object will be ignored.
    /// 
    /// @return bool visible
    ///////////////////////////////////////////////////////////////////
    bool is_visible() const;

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns whether the BaseObject is active in any Room.
    /// @details Active objects are linked to some Room which is held 
    ///     responsible for calling Update and draw regularly as well 
    ///     as enabling other functionality such as collision checks 
    ///     with other objects in the Room. \n\n
    ///     An object can only be active in one Room at a time.
    /// 
    /// @return bool active
    /// 
    /// @see Activate(Room*), Deactivate()
    ///////////////////////////////////////////////////////////////////
    bool is_active() const;


  /////////////////////////////////////////////////////////////////////
  //  Mutator Functions:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Activates the object, making a Room responsible for 
    ///     managing it.
    /// @details The Room responsible for this object will call update
    ///     each step, draw each frame, and may optimize other object
    ///     interactions such as collision checks.
    ///
    /// @param roomPtr A pointer to the Room to activate in
    ///
    /// @pre  The object is not active
    /// @post The object is active
    ///
    /// @see is_active(), Deactivate()
    ///////////////////////////////////////////////////////////////////
    void Activate(Room* roomPtr);

    ///////////////////////////////////////////////////////////////////
    /// @brief Deactivates the object, removing all responsibilities
    ///     of the Room it is in.
    /// @details Deactivating an object
    ///
    /// @pre  The object is active
    /// @post The object is not active
    ///
    /// @see is_active(), Activate(Room*)
    ///////////////////////////////////////////////////////////////////
    void Deactivate();


  /////////////////////////////////////////////////////////////////////
  //  Step and Frame Functions:
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Update Function.
    /// @details This function should hold the code defining how to 
    ///     update after each game step. It will likelly be different 
    ///     for each derived class.
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
    /// @param priority Priority of object
    ///////////////////////////////////////////////////////////////////
    explicit BaseObj(const unsigned int priority = 0);
    
    ///////////////////////////////////////////////////////////////////
    /// @brief Draw the object to a render target.
    /// @details This is a pure virtual function that has to be 
    ///     implemented by the derived class to define how the object
    ///     should be drawn.
    ///
    /// @param target Render target to draw to.
    /// @param states Current render states.
    ///////////////////////////////////////////////////////////////////
    virtual void render(sf::RenderTarget &target, 
                        sf::RenderStates states) const = 0;
    

  /////////////////////////////////////////////////////////////////////
  //  Proctected Data
  /////////////////////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////////////////
    /// @brief The priority of this object's update() and draw() calls.
    /// @details Priority is relative. Between two objects in the same
    ///     Room, the object with the higher _priority will be
    ///     updated and drawn first. It is expected that the object 
    ///     itself will know what the ideal priority is for it at any 
    ///     moment.
    ///////////////////////////////////////////////////////////////////
    signed int _priority;

    ///////////////////////////////////////////////////////////////////
    /// @brief Flag denoting visibility
    /// @details If _visible is false, drawing will be prevented.
    ///////////////////////////////////////////////////////////////////
    bool _visible;


private:

  /////////////////////////////////////////////////////////////////////
  //  Private Functions
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Draws the object to the sf::RenderTarget.
    /// @details Allows the typical SFML draw syntax below:
    ///     @code sf::RenderTarget.draw(sf::Drawable); @endcode
    ///     draw() also enforces visibility functionality before 
    ///     rendering the object via a call to render().
    ///
    /// @param target Render target to draw to.
    /// @param states Current render states.
    ///////////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget &target, 
                      sf::RenderStates states) const final;


  /////////////////////////////////////////////////////////////////////
  //  Private Data
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Pointer the the room this object resides in.
    /// @details _roomHandle == nullptr if and only if the object is 
    ///     inactive.
    ///////////////////////////////////////////////////////////////////
    Room* _roomHandle;


};  //End BaseObj Declaration------------------------------------------




}   //namespace helios-------------------------------------------------

#endif  //HELIOS_BASEOBJ_H
