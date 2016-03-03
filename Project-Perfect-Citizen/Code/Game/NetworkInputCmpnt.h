#pragma once

#include <vector>
#include "../Engine/inputComponent.h"
#include "../Engine/Network.h"
#include "../Engine/debug.h"

namespace ppc {
	class NetworkInputCmpnt : public InputComponent {

	private:

		Network* network_;

		ppc::InputHandler& handle_;

		vector<ppc::DraggableInput*> drags_;

		size_t selectedVert_;
		std::pair<size_t,size_t> selectedEdge_;
		bool clickedVert_;
		bool clickedEdge_;

		void selectEdge(sf::Vector2f);
		void selectVert(sf::Vector2f);
		void loopEdgeColor();

	public:

		NetworkInputCmpnt() = delete;

		NetworkInputCmpnt(Network&, ppc::InputHandler&);

		virtual ~NetworkInputCmpnt();

		virtual bool registerInput(sf::Event& ev) override;

		

	};
};