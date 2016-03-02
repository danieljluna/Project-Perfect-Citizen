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
	sf::FloatRect bounds_;

public:

	Vertex();
	
	Vertex(const Vertex& other);
	Vertex& operator=(const Vertex& other);
	virtual ~Vertex();

	sf::CircleShape& getCircle();

	sf::Color getColor() const;
	void setColor(sf::Color);

	sf::Vector2f getPosCenter() const;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

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
