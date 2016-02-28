#pragma once


#include "inputComponent.h"
#include "Network.h"


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