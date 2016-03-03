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

	public:

		NetworkInputCmpnt() = delete;

		NetworkInputCmpnt(Network&, ppc::InputHandler&);

		~NetworkInputCmpnt();

		virtual bool registerInput(sf::Event& ev) override;

		

	};
};