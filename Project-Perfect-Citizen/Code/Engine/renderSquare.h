#ifndef PPC_RENDER_SQUARE
#define PPC_RENDER_SQUARE

#include "renderComponent.h"

//For the moment this class is defunct

class RenderSquare : public ppc::RenderComponent {
private:
	int area;
	sf::RectangleShape* rect;

public:
	void render(sf::RenderWindow* wnd);
	RenderSquare();

};

#endif
