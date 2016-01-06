#ifndef PPC_WINDOW_H
#define PPC_WINDOW_H
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include "ppc_entity.h"


namespace ppc {



class Window : public sf::RectangleShape {
public:

	bool intersectsMouse(sf::Vector2i &mouse_position);
	Window(float w, float h, float x, float y);

private:
	
};


}   //End namespace ppc


#endif  //End PPC_WINDOW_H

