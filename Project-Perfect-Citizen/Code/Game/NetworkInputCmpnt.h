#pragma once


#include "../Engine/inputComponent.h"
#include "../Engine/Network.h"
#include "../Engine/debug.h"

namespace ppc {
	class NetworkInputCmpnt : public InputComponent {

	private:

		Network* network_;

	public:

		NetworkInputCmpnt() = delete;

		NetworkInputCmpnt(Network&);

		~NetworkInputCmpnt();

		virtual bool registerInput(sf::Event& ev) override;

	};
};