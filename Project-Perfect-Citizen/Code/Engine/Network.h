#ifndef NETWORK_H
#define NETWORK_H

#include <cstddef>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include "Vertex.h"
#include "Edge.h"


namespace ppc {


class Network : public sf::Drawable {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    Network(size_t size = 0);


  /////////////////////////////////////////////////////////////////////
  // Vertex Manipulation
  /////////////////////////////////////////////////////////////////////

    void setSize(size_t size);


  /////////////////////////////////////////////////////////////////////
  // Edge Manipulation
  /////////////////////////////////////////////////////////////////////

    void clearEdges(size_t index);

    void clearIncomingEdges(size_t index);

    void clearOutgoingEdges(size_t index);

    void removeEdge(size_t start, size_t end);

    void setEdge(size_t start, size_t end, const Edge& e);


  /////////////////////////////////////////////////////////////////////
  // Getters
  /////////////////////////////////////////////////////////////////////

    Vertex& vert(size_t index);
    
    const Vertex& vert(size_t index) const;

    Edge* edge(size_t start, size_t end);

    const Edge* edge(size_t start, size_t end) const;

    Edge* operator()(size_t start, size_t end);

    const Edge* operator()(size_t start, size_t end) const;
    
    Vertex& operator[](size_t index);

    const Vertex& operator[](size_t index) const;
    
    bool isAdjacent(size_t start, size_t end) const;

    size_t size() const;


private:

  /////////////////////////////////////////////////////////////////////
  // Drawable Functionality
  /////////////////////////////////////////////////////////////////////

    void draw(sf::RenderTarget& target, 
              sf::RenderStates states) const override;


  /////////////////////////////////////////////////////////////////////
  // Helper Functions
  /////////////////////////////////////////////////////////////////////

    void clearData();
    
    size_t getEdgeIndex(size_t source, size_t dest) const;
    
    bool rangeCheck(size_t index) const;

    void rangeExcep(size_t index) const;

    void removeEdge(size_t index);


  /////////////////////////////////////////////////////////////////////
  // Private Variables
  /////////////////////////////////////////////////////////////////////

    size_t size_;
    
    Edge** edgeMat_;

    std::vector<Vertex> vertexData_;

    float vertSize_;

    unsigned int edgeCount_;


};


};      //End namespace mdg


#endif  //End NETWORK_H
