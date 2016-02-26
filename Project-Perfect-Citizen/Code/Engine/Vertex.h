#ifndef VERTEX_H
#define VERTEX_H

#include <SFML/Graphics/Sprite.hpp>

namespace ppc {


class Vertex: public sf::Drawable {

private:

	sf::Color color_;

	sf::Vector2f pos_;


public:

	Vertex();
	Vertex(sf::Vector2f, sf::Color);
	Vertex(float, float, sf::Color);
	
	~Vertex();


	sf::Color getColor() const;
	void setColor(sf::Color);

	sf::Vector2f getPos() const;
	void setPos(sf::Vector2f);
	void setPos(float x, float y);

	virtual void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;
};


};      //End namespace mdg


#endif  //End VERTEX_H
