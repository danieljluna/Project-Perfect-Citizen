#pragma once

#include <vector>
#include "../Engine/inputComponent.h"
#include "../Engine/Network.h"
#include "PipelineDataRenderComponent.h"

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief Class that allows interactability with Network Graphs.
	/// @author Mark Biundo & Nader Sleem
	///////////////////////////////////////////////////////////////////
	class NetworkInputCmpnt : public InputComponent {
		//class Edge;

	private:

		Network* network_;
		Network* solution_;

		ppc::InputHandler& handle_;

		std::vector<ppc::DraggableInput*> drags_;

		size_t selectedVert_;
		std::pair<size_t,size_t> selectedEdge_;
		bool clickedVert_;
		bool clickedEdge_;

		void selectEdge(sf::Vector2f);
		void unselectEdge(Edge& e);
		void selectVert(sf::Vector2f);
		void loopEdgeColor();

		PipelineDataRenderComponent* pipeRender_;
		void updateDataText();

	public:

		NetworkInputCmpnt() = delete;

		///////////////////////////////////////////////////////////////
		///@brief Ctor
		///@param net The player's version of the Network
		///@param sol The solution Network.
		///@param ih The input handle of the Window the graph is going
		///	to be in.
		///////////////////////////////////////////////////////////////
		NetworkInputCmpnt(Network&, Network&, ppc::InputHandler&);

		std::vector<ppc::DraggableInput*>* getDraggables();

		void setPipelineData(PipelineDataRenderComponent&);

        void setClampBounds(const sf::FloatRect clampBounds);

        void unBoundDraggables();

		virtual ~NetworkInputCmpnt();

		virtual bool registerInput(Event ev) override;

		

	};
};
