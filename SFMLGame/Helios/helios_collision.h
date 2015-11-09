#ifndef HELIOS_COLLISION_H
#define HELIOS_COLLISION_H


#include <list>

#include "helios_main.h"

// @brief Defines a quadtree with each node having four children

namespace helios {
    class QuadTree {
    public:
    //Constructors & Destructors:

      //Default Constructor
        QuadTree();
      //Copy Constructor
        QuadTree(const QuadTree& other);
      //Move Constructor
        QuadTree(QuadTree&& other);
      //Destructor
        ~QuadTree();

    //Operators:

      //Copy Assignment Operator
        QuadTree operator=(const QuadTree& other);
      //Move Assignment Operator
        QuadTree operator=(QuadTree&& other);

    private:
        // \brief 
        class Node {
        public:
        //Constructors:

          //No Default Constructor
            Node() = delete;
          //Copy Constructor
            Node(const Node& other);
          //Move Constructor
            Node(Node&& other);
          //Destructor
            ~Node();

        //Operators:

          //Copy Assignment Operator
            Node operator=(const Node& other);
          //Move Assignment Operator
            Node operator=(Node&& other);

        private:
        //Private Fields:

          //Pointers to the next 4 nodes.
            Node *northeast, *northwest, *southeast, *southwest;
          //Structure to hold objects.
            std::list<BaseObj> objectList;
        };
    };
};

#endif  //HELIOS_COLLISION_H
