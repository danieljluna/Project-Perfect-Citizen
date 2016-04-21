#pragma once
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "../Engine/NotificationObserver.h"

namespace ppc {

	class notificationRenderComponent : public ppc::RenderComponent {
	private:
		sf::CircleShape badge_;
		mutable sf::Text notificationText_;
        sf::Vector2f position_;
		//value recieved from notiObserver
		//unsigned int notiValue;
	public:
		notificationRenderComponent();
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
		ppc::NotificationObserver& getNotiObserver();
		//notivalue is recieved from NotiObserver when it gets an update
		//updates the notificationText_ to properly display how many updates are left. 
		void updateText(unsigned int notiValue) const;
		ppc::NotificationObserver notiObserver_;

        void setPosition(sf::Vector2f pos);


	};
};