#include <SFML/Graphics.hpp>
#include <>

namespace Helios {
    /*
    \breif Describes a given space and the objects that exist within it in
        in a way that facilitates consistent generation.
    */
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
        unsigned int draw() const;

    private:

    //Private Fields:

      //
        BaseObj** ObjList;

    };


    /*
    \breif An abstract class providing the basis for packaging a sprite with
       the appropriate logic functions all objects in the room need.
    */
    class BaseObj {
    public:

    //Constructors & Destructors:

      //Default Constructor
        BaseObj();
      //Copy Constructor
        BaseObj(const BaseObj& other);
      //Move Constructor
        BaseObj(BaseObj&& other);
      //Destructor
        ~BaseObj();

    //Operators:

        //Copy Assignment Operator
        BaseObj& operator=(const BaseObj& other);
        //Move Assignment Operator
        BaseObj& operator=(BaseObj&& other);
    
    //Step & Frame Functions:

      //Called each step
        virtual unsigned int update() = 0;
      //Called on each frame
        virtual unsigned int draw() const = 0;

    private:

    //Private Fields:

        //Contains the visual representation of the object
        sf::Sprite sprite;
        //Should prevent draw function from executing
        bool visible;
        //Should prevent update and draw function from executing
        bool active;
    };

}