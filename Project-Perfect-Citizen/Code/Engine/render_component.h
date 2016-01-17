#ifndef PPC_CMPNT_RENDER
#define PPC_CMPNT_RENDER
#include "ppc_component.h"
#include <SFML/Graphics.hpp>
class RenderComponent : public Component {
private:
	int tempVar;
public:
	//virtual RenderComponent* init() = 0;
	virtual void render(sf::RenderWindow* wnd) = 0;
};
#endif
