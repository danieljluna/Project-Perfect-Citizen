#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../Engine/Engine.h"
//#include "desktop.h"
//#include "InputHandler.h"
#include "../Game/Database.h"
#include "../Game/Inbox.h"

namespace ppc {

	class IconBuilder {
	private:

		Desktop* dt;
		InputHandler* ih;
		ppc::Database* db;
		ppc::Inbox* ib;
		sf::Image* buttonSheet;

		sf::Font* font;
		sf::Color fontColor;

		std::string label;
		std::string isBeingPressed;

		int sheetX;
		int sheetY;
		int width;
		int frames;

		float size;
		float animationSpeed;

		float posX;
		float posY;

	public:
		IconBuilder();

		~IconBuilder();

		void setSpritebyIndicies(int x, int y, int r, int f);

		void setSprites(sf::Sprite&, sf::Sprite&);

		void setSize(float s);

		void setDesktop(ppc::Desktop&);

		void setInputHandle(ppc::InputHandler&);

		void setButtonSheet(sf::Image&);

		void setDatabase(ppc::Database&);

		void setInbox(ppc::Inbox&);

		void setText(std::string, sf::Font&, sf::Color);

		void setAnimSpeed(float spd);

		void setPosition(float x, float y);

		void setPosition(sf::Vector2f pos);

///////////////////////////////////////////////////////////////////////
/// @brief Returns the constructed icon
///////////////////////////////////////////////////////////////////////
		void create(Entity&);


	};
};