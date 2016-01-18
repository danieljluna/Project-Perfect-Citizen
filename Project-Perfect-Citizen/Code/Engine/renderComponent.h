#ifndef PPC_CMPNT_RENDER
#define PPC_CMPNT_RENDER

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <vector>

class RenderComponent : public ppc::Component, public sf::Drawable {
private:
	int tempVar;

public:
	//virtual RenderComponent* init() = 0;
	virtual void render(sf::RenderWindow* wnd) = 0;
    static std::vector<RenderComponent*> renderVector;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	void removeElement(int index);
};

#endif
