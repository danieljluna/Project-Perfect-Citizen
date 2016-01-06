#ifndef PPC_WINDOW_H
#define PPC_WINDOW_H
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include "ppc_entity.h"


namespace ppc {



class Window : public sf::RectangleShape {
public:

	Window(float w, float h);

private:
	
};


}   //End namespace ppc


#endif  //End PPC_WINDOW_H

