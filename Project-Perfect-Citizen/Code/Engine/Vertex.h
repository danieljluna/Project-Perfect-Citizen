#ifndef VERTEX_H
#define VERTEX_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "DraggableInput.h"
#include "../Game/PipelineCharacter.h"

namespace ppc {


class Vertex: public sf::Drawable, public sf::Transformable {

private:

	sf::Color color_;

	sf::Text text_;
	sf::Font font_;
	static const int fontSize_;

	PipelineCharacter char_;

	sf::CircleShape circ_;
	static const float radius_;

	void setTextPos();

public:

	Vertex();
	Vertex(sf::Vector2f, PipelineCharacter, sf::Color);
	Vertex(float, float, PipelineCharacter, sf::Color);
	
	Vertex(const Vertex& other);
	Vertex& operator=(const Vertex& other);
	virtual ~Vertex();

	sf::CircleShape& getCircle();

	sf::Color getColor() const;
	void setColor(sf::Color);

	sf::Vector2f getPos() const;
	void setPos(sf::Vector2f);
	void setPos(float x, float y);


	sf::Vector2f getPosCenter() const;

	PipelineCharacter getCharacter() const;
	void setCharacter(PipelineCharacter);

	void setTextFont(sf::Font);
	void setTextFontLoad(std::string font);

	void applyDraggable(ppc::DraggableInput&,ppc::InputHandler&);

	virtual void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;
};


};      //End namespace mdg


#endif  //End VERTEX_H
