#include "Network.h"
#include "debug.h"


#include <cassert>
#include <cmath>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace ppc;

const float thickness = 3.f;

Network::Network(size_t size) {
    size_ = size;
    edgeMat_ = new Edge*[size * size];
    vertexData_ = new Vertex[size];

    //Init all edges to null
    for (size_t e = 0; e < size * size; ++e) {
        edgeMat_[e] = nullptr;
    }

    //Drawing Vars
    vertSize_ = 15.0f;
    edgeCount_ = 0;
	drawTempEdge_ = false;
}


Network::~Network() {
    delete[] edgeMat_;
    delete[] vertexData_;
}

///////////////////////////////////////////////////////////////////
// Solution Checking
///////////////////////////////////////////////////////////////////
bool Network::checkCenterEquality(const Network& other) {
	if (size_ != other.size()) return false;
	return (center_ == other.getCenter());
}

float Network::checkEdgeEquality(const Network& other) {
	float points = 0.f;
	float numVisited = 0.f;
	for (unsigned int i = 0; i < size_; ++i) {
		for (unsigned int j = i + 1; j < size_; ++j) {
			if (isAdjacent(i, j)) {
				numVisited += 2;
				if (other.isAdjacent(i, j)) {
					points += 1;
					//numVisited += 1;
					sf::Color thiscolor = edge(i, j)->getColor();
					sf::Color thatcolor = other.edge(i, j)->getColor();
					if (thiscolor == sf::Color::Red || thiscolor == selRed) {
						if (thatcolor == sf::Color::Red || thatcolor == selRed) ++points;
					}
					if (thiscolor == sf::Color::Green || thiscolor == selGreen) {
						if (thatcolor == sf::Color::Green || thiscolor == selGreen) ++points;
					}
				}
			}
		}
	}
	return points/numVisited;
}

float Network::checkColorlessEdgeEquality(const Network& other) {
	float points = 0.f;
	float numVisited = 0.f;
	for (unsigned int i = 0; i < size_; ++i) {
		for (unsigned int j = i + 1; j < size_; ++j) {
			if (isAdjacent(i, j) == other.isAdjacent(i, j)) ++points;
			++numVisited;
		}
	}
	return points/numVisited;
}


///////////////////////////////////////////////////////////////////////
// Vertex Manipulation
///////////////////////////////////////////////////////////////////////

void Network::setSize(size_t size) {
    Edge** newEdgeMat = new Edge*[size * size];
    Vertex* newVertexData = new Vertex[size];
    edgeCount_ = 0;

    //For all sources:
    for (size_t i = 0; i < size; ++i) {

        //If we have data on previous Verts
        if (i < size_) {
            //Copy over Vertex Data
            newVertexData[i] = std::move(vertexData_[i]);
        }

        //For all edge pairs:
        for (size_t j = 0; j < size; ++j) {
            //When both verts exist across resize:
            if ((i < size_) && (j < size_)) {
                //Keep the original edges relationship:
                size_t edgeCurrIndex = getEdgeIndex(i, j);
                newEdgeMat[(i * size_) + j] = edgeMat_[edgeCurrIndex];
                edgeMat_[edgeCurrIndex] = nullptr;
                ++edgeCount_;   //Be sure to count Edges
            } else {
                //Initialize Edge* to nullptr
                newEdgeMat[(i * size_) + j] = nullptr;
            }
        }

    }   //End for loop of i over verts

        //Clear data
    clearEdges();

    //Copy over data
    edgeMat_ = newEdgeMat;
    vertexData_ = newVertexData;

}

Network * ppc::Network::copyNetworkByVerts() {
	Network* newNet = new Network(size_);
	for (unsigned int i = 0; i < size_; ++i) {
		newNet->vert(i) = vert(i);
	}
	return newNet;
}


void Network::setCenter(unsigned int cent) {
	center_ = cent;
    //Create Event
	unsigned int neg1 = -1;
	if (cent == neg1) return;
    Event ev;
    ev.type = ev.NetworkType;
    ev.network.type = ev.network.Center;
    ev.network.u = cent;
    ev.network.v = -1;
    ev.network.net = this;
    onManip().sendEvent(ev);
}




///////////////////////////////////////////////////////////////////////
// Edge Manipulation
///////////////////////////////////////////////////////////////////////

void Network::clearEdges(size_t index) {
    assert(rangeCheck(index));

    clearIncomingEdges(index);
    clearOutgoingEdges(index);
}


void Network::clearIncomingEdges(size_t index) {
    assert(rangeCheck(index));

    //If we have a valid index
    if (rangeCheck(index)) {
        //Find the first Edge ending at the indexed vert
        size_t e0 = getEdgeIndex(0, index);

        //Remove every size-th edge
        for (size_t i = 0; i < size_; ++i) {
            removeEdge(e0 + (i * size_));
        }
    }
}


void Network::clearOutgoingEdges(size_t index) {
    assert(rangeCheck(index));

    //If we have a valid index
    if (rangeCheck(index)) {
        //Find the first Edge starting at the indexed vert
        size_t e0 = getEdgeIndex(index, 0);

        //Remove the next size_ edges
        for (size_t i = 0; i < size_; ++i) {
            removeEdge(e0 + i);
        }
    }
}


void Network::removeEdge(size_t start, size_t end) {
    assert(rangeCheck(start));
    assert(rangeCheck(end));

    //If we have valid verts:
    if (rangeCheck(start) && rangeCheck(end) && isAdjacent(start, end)) {
        //Remove the edge
        removeEdge(getEdgeIndex(start, end));

        //Create Event
        Event ev;
        ev.type = ev.NetworkType;
        ev.network.type = ev.network.Removed;
        ev.network.u = start;
        ev.network.v = end;
        ev.network.net = this;
        onManip().sendEvent(ev);
    }
}


void Network::setEdge(size_t start, size_t end, const Edge& e) {
    rangeExcep(start);
    rangeExcep(end);

    //Find the index of the edge in question
    size_t eIndex = getEdgeIndex(start, end);

    //Create Event
    Event ev;
    ev.type = ev.NetworkType;
    ev.network.u = start;
    ev.network.v = end;
    ev.network.net = this;

    if (isAdjacent(start, end)) {
        ev.network.type = ev.network.Edited;
    } else {
        ev.network.type = ev.network.Created;
    }

    //Remove any edge here,
    removeEdge(start, end);

    //Then add an Edge
    edgeMat_[eIndex] = new Edge(e);
    ++edgeCount_;

    onManip().sendEvent(ev);
}




///////////////////////////////////////////////////////////////////////
// Getters
///////////////////////////////////////////////////////////////////////

Vertex& Network::vert(size_t index) {
    rangeExcep(index);
    return vertexData_[index];
}


const Vertex& Network::vert(size_t index) const {
    rangeExcep(index);
    return vertexData_[index];
}


Edge* Network::edge(size_t start, size_t end) {
    rangeExcep(start);
    rangeExcep(end);

    return edgeMat_[getEdgeIndex(start, end)];
}


const Edge* Network::edge(size_t start, size_t end) const {
    rangeExcep(start);
    rangeExcep(end);

    return edgeMat_[getEdgeIndex(start, end)];
}


Edge* Network::operator()(size_t start, size_t end) {
    return edgeMat_[getEdgeIndex(start, end)];
}


const Edge* Network::operator()(size_t start, size_t end) const {
    return edgeMat_[getEdgeIndex(start, end)];
}


Vertex& Network::operator[](size_t index) {
    return vertexData_[index];
}


const Vertex& Network::operator[](size_t index) const {
    return vertexData_[index];
}


bool Network::isAdjacent(size_t start, size_t end) const {
    assert(rangeCheck(start));
    assert(rangeCheck(end));
    return (edgeMat_[getEdgeIndex(start, end)] != nullptr);
}


size_t Network::size() const {
    return size_;
}

unsigned int Network::getCenter() const {
	return center_;
}


///////////////////////////////////////////////////////////////////////
// Drawable Functionality
///////////////////////////////////////////////////////////////////////

void Network::draw(sf::RenderTarget& target,
    sf::RenderStates states) const {
	//Define Vertex Shape:
	//sf::CircleShape vertShape(vertSize_);
	//vertShape.setOrigin(vertSize_, vertSize_);

	unsigned int lineVerts = 2 * edgeCount_;
	if (drawTempEdge_) lineVerts += 4;
	//unsigned int lineVerts = 4;
	sf::VertexArray edgeLines(sf::Quads, lineVerts);
	unsigned int linesDrawn = 0;
	
	for (size_t i = 0; i < size_; ++i) {
		for (size_t j = i + 1; j < size_; ++j) {
			if (isAdjacent(i, j)) { //draw it
				size_t edgeIndex = getEdgeIndex(i, j);

				sf::Vector2f point1 = vertexData_[i].getPosCenter();
				sf::Vector2f point2 = vertexData_[j].getPosCenter(); 

				sf::Vector2f direction = point2 - point1;
				sf::Vector2f unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
				sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

				sf::Vector2f offset = (thickness / 2.f)*unitPerpendicular;

				edgeLines[linesDrawn * 4].position = point1 + offset;
				edgeLines[linesDrawn * 4 + 1].position = point2 + offset;
				edgeLines[linesDrawn * 4 + 2].position = point2 - offset;
				edgeLines[linesDrawn * 4 + 3].position = point1 - offset;

				edgeLines[linesDrawn * 4].color = edgeMat_[edgeIndex]->getColor();
				edgeLines[linesDrawn * 4 + 1].color = edgeMat_[edgeIndex]->getColor();
				edgeLines[linesDrawn * 4 + 2].color = edgeMat_[edgeIndex]->getColor();
				edgeLines[linesDrawn * 4 + 3].color = edgeMat_[edgeIndex]->getColor();

				//Adjust the bounds of the edge based on
				//where it is drawn.
				edgeMat_[edgeIndex]->constructBounds(
					vertexData_[i].getPosCenter(),
					vertexData_[j].getPosCenter());
				
				linesDrawn++;
			}
		}
	}

	if (drawTempEdge_) {
		sf::Vector2f point1 = vertexData_[tempEdgeSource_].getPosCenter();
		float mosx = static_cast<float>(sf::Mouse::getPosition().x);
		float mosy = static_cast<float>(sf::Mouse::getPosition().y);
		sf::Vector2f point2{ mosx, mosy };

		sf::Vector2f direction = point2 - point1;
		sf::Vector2f unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
		sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

		sf::Vector2f offset = (thickness / 2.f)*unitPerpendicular;

		edgeLines[linesDrawn * 4].position = point1 + offset;
		edgeLines[linesDrawn * 4 + 1].position = point2 + offset;
		edgeLines[linesDrawn * 4 + 2].position = point2 - offset;
		edgeLines[linesDrawn * 4 + 3].position = point1 - offset;

		edgeLines[linesDrawn * 4].color = tempEdgeColor_;
		edgeLines[linesDrawn * 4 + 1].color = tempEdgeColor_;
		edgeLines[linesDrawn * 4 + 2].color = tempEdgeColor_;
		edgeLines[linesDrawn * 4 + 3].color = tempEdgeColor_;
	}

	target.draw(edgeLines, states);

	/*
	Thin lines -- Deprecated

	//Define vars for lines
    unsigned int lnVerts = 2 * edgeCount_;
	sf::VertexArray edgeLines(sf::Lines, 2 * edgeCount_);
    unsigned int lnsDrawn = 0;

    for (size_t i = 0; i < size_; ++i) {

        //For each edge leaving this Vertex
        for (size_t j = 0; (lnsDrawn < lnVerts) && (j < size_); ++j) {
            //If it exists:
            size_t edgeIndex = getEdgeIndex(i, j);
            if (edgeMat_[edgeIndex] != nullptr) {
                //Add point i to the edgeLines to draw
                edgeLines[lnsDrawn].position = vertexData_[i].getPosCenter();
                edgeLines[lnsDrawn].color = edgeMat_[edgeIndex]->getColor();

                //Add point j to the edgeLines to draw
				edgeLines[++lnsDrawn].position = vertexData_[j].getPosCenter();
                edgeLines[lnsDrawn].color = edgeMat_[edgeIndex]->getColor();
                ++lnsDrawn;
				
				//Adjust the bounds of the edge based on
				//where it is drawn.
				edgeMat_[edgeIndex]->constructBounds(
					vertexData_[i].getPosCenter(),
					vertexData_[j].getPosCenter());
            }
        }

    }

	//Draw the edges
	target.draw(edgeLines, states);
	*/

	//For each Vertex
	for (size_t i = 0; i < size_; ++i) {
		//Draw that Vertex
		target.draw(vertexData_[i], states);
	}

}

///////////////////////////////////////////////////////////////////////
// Extra functions for Drawing
///////////////////////////////////////////////////////////////////////

void Network::setTempEdgePos(unsigned int vertnum) {
	tempEdgeSource_ = vertnum;
}

void Network::setTempEdgeDraw(bool set) {
	drawTempEdge_ = set;
}

void Network::setTempColorBlack() {
	tempEdgeColor_ = sf::Color::Black;
}

void Network::setTempColorGreen() {
	tempEdgeColor_ = sf::Color::Green;
}

void Network::setTempColorRed() {
	tempEdgeColor_ = sf::Color::Red;
}

///////////////////////////////////////////////////////////////////////
// Check Helper Functions
///////////////////////////////////////////////////////////////////////

void Network::clearEdges() {
    //Clear out edgeMat_
    for (size_t i = 0; i < size_; ++i) {
        removeEdge(i);
    }
}


size_t Network::getEdgeIndex(size_t source, size_t dest) const {
    return ((source * size_) + dest);
}


bool Network::rangeCheck(size_t index) const {
    return (index < size_);
}


void Network::rangeExcep(size_t index) const {
    if (index >= size_) {
        std::out_of_range("Network::__rangeExcep__");
    }
}


void Network::removeEdge(size_t index) {
    if (edgeMat_[index] != nullptr) {
        delete edgeMat_[index];
        edgeMat_[index] = nullptr;
        --edgeCount_;
    }
}


