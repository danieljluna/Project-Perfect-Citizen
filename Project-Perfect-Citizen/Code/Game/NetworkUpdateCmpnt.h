#pragma once

#include <vector>
#include "../Engine/updateComponent.h"
#include "../Engine/Network.h"


namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief Update Component for Networks
	///@details Mainly used to prevent Vetices from being dragged off
	///	a given bounding area.
	///////////////////////////////////////////////////////////////////
	class NetworkUpdateCmpnt : public UpdateComponent {

	private:

		Network* network_;

		sf::FloatRect bounds_;

		vector<ppc::DraggableInput*>* drags_;

	public:

		NetworkUpdateCmpnt() = delete;
		NetworkUpdateCmpnt(Network&);
		NetworkUpdateCmpnt(Network&, sf::FloatRect);

		void setBounds(sf::FloatRect);

		void setDrags(vector<ppc::DraggableInput*>*);

		virtual void update(sf::Time& deltaTime) override;

		

	};
};
