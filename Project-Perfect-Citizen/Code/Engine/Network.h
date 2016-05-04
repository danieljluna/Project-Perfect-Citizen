#ifndef NETWORK_H
#define NETWORK_H

#include <cstddef>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include "Vertex.h"
#include "Edge.h"
#include "debug.h"


namespace ppc {


    ///////////////////////////////////////////////////////////////////////
    /// @brief Describes a directional graph consisting of vertices and 
    ///     their edges.
    /// @details This class uses an array of vertices an an adjacency 
    ///     matrix to define the directional graph. Asserts exist for all
    ///     vertex index parameters on top of documented checks. This class
    ///     is closely tied to the Vertex and Edge classes, and should one
    ///     day be templated.
    ///////////////////////////////////////////////////////////////////////
    class Network : public sf::Drawable {
    public:

		///////////////////////////////////////////////////////////////
        // Constructors & Destructor
		///////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////
        /// @brief Constructor
        /// @details Creates an empty map with the given number of 
        ///     Vertices.
        ///
        /// @param size The number of Vertices to spawn with.
		///////////////////////////////////////////////////////////////
        Network(size_t size = 0);

		///////////////////////////////////////////////////////////////
        /// @brief Destructors
		///////////////////////////////////////////////////////////////
        ~Network();

		///////////////////////////////////////////////////////////////////
		// Solution Checking
		///////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////
		/// @brief Center Equality Check
		/// @details compares another network graph to this one, and checks
		///     if their node labled "center" is the same.  Naive checking
		///     currently.  Only checks if the graphs are same size and have
		///     the same center index.  Does not investigate content of nodes
		///     so it's up to the programmer to make sure the graphs being
		///     compared make sense.
		/// @param [in] other A network graph
		///////////////////////////////////////////////////////////////////
		bool checkCenterEquality(const Network& other);

		///////////////////////////////////////////////////////////////////
		/// @brief Edge Equality Check
		/// @details Loops through all nodes, looking at all edges attached
		///     to that node in both graphs.  Assumes equivalent nodes have 
		///     same indeces in both graphs.  Assumes the player has run a
		///     Center Equality Check.
		/// @param [in] other A network graph
		///////////////////////////////////////////////////////////////////
		float checkEdgeEquality(const Network& other);

		///////////////////////////////////////////////////////////////
        // Vertex Manipulation
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
        /// @brief Sets the size of the Network.
		///////////////////////////////////////////////////////////////
        void setSize(size_t size);

		///////////////////////////////////////////////////////////////
		///@brief Return a new copy of this network with only the vertices
		///////////////////////////////////////////////////////////////
		Network* copyNetworkByVerts();

		///////////////////////////////////////////////////////////////////
		/// @brief Set the index for the network's "Center"
		///////////////////////////////////////////////////////////////////
		void setCenter(unsigned int cent);

		///////////////////////////////////////////////////////////////
        // Edge Manipulation
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
        /// @brief Clears all edges connected to the given vertex.
        ///
        /// @param index The index of the vertex to clear edges from.
		///////////////////////////////////////////////////////////////
        void clearEdges(size_t index);

		///////////////////////////////////////////////////////////////
        /// @brief Clears all edges ending at a given vertex.
        ///
        /// @param index The index of the vertex to clear edges from.
		///////////////////////////////////////////////////////////////
        void clearIncomingEdges(size_t index);

		///////////////////////////////////////////////////////////////
        /// @brief Clears all edges starting at a given vertex.
        ///
        /// @param index The index of the vertex to clear edges from.
		///////////////////////////////////////////////////////////////
        void clearOutgoingEdges(size_t index);

		///////////////////////////////////////////////////////////////
        /// @brief Removes the edge between the given vertices.
        /// @details If the edge does not exist, nothing happens.
        ///
        /// @param start The index of the vertex that the edge starts at.
        /// @param end The index of the vertex that the edge ends at.
		///////////////////////////////////////////////////////////////
        void removeEdge(size_t start, size_t end);

		///////////////////////////////////////////////////////////////
        /// @brief Sets the edge between the given vertices
        ///
        /// @param start The index of the vertex that the edge starts at.
        /// @param end The index of the vertex that the edge ends at.
        /// @param e The edge to copy in.
		///////////////////////////////////////////////////////////////
        void setEdge(size_t start, size_t end, const Edge& e);


		///////////////////////////////////////////////////////////////
        // Getters
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
        /// @brief Returns the vertex at the given index.
        ///
        /// @pre 0 < index < size()
        /// @throw Throws an out_of_range error if precondition fails.
        /// @param index The index of the vertex to return.
		///////////////////////////////////////////////////////////////
        Vertex& vert(size_t index);

		///////////////////////////////////////////////////////////////
        /// @copydoc Network::vert(size_t)
		///////////////////////////////////////////////////////////////
        const Vertex& vert(size_t index) const;

		///////////////////////////////////////////////////////////////
        /// @brief Returns the Edge connecting the given vertices.
        ///
        /// @pre (0 < start < size()) && (0 < end < size())
        /// @throw Throws an out_of_range error if precondition fails.
        /// @param start The index of the vertex that the edge starts at.
        /// @param end The index of the vertex that the edge ends at.
		///////////////////////////////////////////////////////////////
        Edge* edge(size_t start, size_t end);

		///////////////////////////////////////////////////////////////
        /// @copydoc Network::edge(size_t)
		///////////////////////////////////////////////////////////////
        const Edge* edge(size_t start, size_t end) const;

		///////////////////////////////////////////////////////////////
        /// @brief Returns the Edge connecting the given vertices.
        ///
        /// @pre (0 < start < size()) && (0 < end < size())
        /// @param start The index of the vertex that the edge starts at.
        /// @param end The index of the vertex that the edge ends at.
		///////////////////////////////////////////////////////////////
        Edge* operator()(size_t start, size_t end);

		///////////////////////////////////////////////////////////////
        /// @copydoc Network::operator()(size_t,size_t)
		///////////////////////////////////////////////////////////////
        const Edge* operator()(size_t start, size_t end) const;

		///////////////////////////////////////////////////////////////
        /// @brief Returns the vertex at the given index.
        ///
        /// @pre 0 < index < size()
        /// @param index The index of the vertex to return.
		///////////////////////////////////////////////////////////////
        Vertex& operator[](size_t index);

		///////////////////////////////////////////////////////////////
        /// @copydoc Network::operator[](size_t)
		///////////////////////////////////////////////////////////////
        const Vertex& operator[](size_t index) const;

		///////////////////////////////////////////////////////////////
        /// @brief Returns whether there is an edge between the given 
        ///     vertices.
        ///
        /// @pre (0 < start < size()) && (0 < end < size())
        /// @throw Throws an out_of_range error if precondition fails.
        /// @param start The index of the vertex that the edge starts at.
        /// @param end The index of the vertex that the edge ends at.
		///////////////////////////////////////////////////////////////
        bool isAdjacent(size_t start, size_t end) const;

		///////////////////////////////////////////////////////////////
        /// @brief Returns the number of vertices in the Network.
		///////////////////////////////////////////////////////////////
        size_t size() const;

		///////////////////////////////////////////////////////////////////
		/// @brief Returns the index of the graph's "center"
		///////////////////////////////////////////////////////////////////
		unsigned int getCenter() const;


        ///////////////////////////////////////////////////////////////
        /// @brief Returns Network Manipulation Subject
        ///////////////////////////////////////////////////////////////
        Subject& onManip() { return onManip_; };


    private:

		///////////////////////////////////////////////////////////////
        // Drawable Functionality
		///////////////////////////////////////////////////////////////

        void draw(sf::RenderTarget& target,
            sf::RenderStates states) const override;


		///////////////////////////////////////////////////////////////
        // Helper Functions
		///////////////////////////////////////////////////////////////

        //Removes all edges in edgeMat_
        void clearEdges();

        //Gets the index in the 1D array of the edge
        size_t getEdgeIndex(size_t source, size_t dest) const;

        //Checks if the index is valid (nothrow)
        bool rangeCheck(size_t index) const;

        //Throws if the index is invalid
        void rangeExcep(size_t index) const;

        //Removes the edge if it exists
        void removeEdge(size_t index);

		
		///////////////////////////////////////////////////////////////
        // Private Variables
		///////////////////////////////////////////////////////////////

        size_t size_;

        Edge** edgeMat_;

        Vertex* vertexData_;

        float vertSize_;

        unsigned int edgeCount_;

		unsigned int center_;

        Subject onManip_;

    };


};      //End namespace mdg

		
#endif  //End NETWORK_H
