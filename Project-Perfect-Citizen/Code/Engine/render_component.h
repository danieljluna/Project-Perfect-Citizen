#ifndef PPC_CMPNT_RENDER
#define PPC_CMPNT_RENDER

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <vector>

class RenderComponent : public ppc::Component {
private:
	int tempVar;

public:
	//virtual RenderComponent* init() = 0;
	virtual void render(sf::RenderWindow* wnd) = 0;

    static std::vector<sf::Sprite*> renderVector;

};

#endif
