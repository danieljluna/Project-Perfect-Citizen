#ifndef PPC_RENDER_SQUARE
#define PPC_RENDER_SQUARE

#include "renderComponent.h"

//Test class is showing an example of render
class RenderSquare : public RenderComponent {
private:
	int area;
	sf::RectangleShape* rect;

public:
	void render(sf::RenderWindow* wnd);
	RenderSquare();

};

#endif
