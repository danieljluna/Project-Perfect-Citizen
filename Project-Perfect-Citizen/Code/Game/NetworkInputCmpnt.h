#pragma once

#include <vector>
#include "../Engine/inputComponent.h"
#include "../Engine/Network.h"
#include "PipelineDataRenderComponent.h"

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief Class that allows interactability with Network Graphs.
	///////////////////////////////////////////////////////////////////
	class NetworkInputCmpnt : public InputComponent {

	private:

		Network* network_;
		Network* solution_;

		ppc::InputHandler& handle_;

		vector<ppc::DraggableInput*> drags_;

		size_t selectedVert_;
		std::pair<size_t,size_t> selectedEdge_;
		bool clickedVert_;
		bool clickedEdge_;

		void selectEdge(sf::Vector2f);
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

		vector<ppc::DraggableInput*>* getDraggables();

		void setPipelineData(PipelineDataRenderComponent&);

		virtual ~NetworkInputCmpnt();

		virtual bool registerInput(sf::Event& ev) override;

		

	};
};