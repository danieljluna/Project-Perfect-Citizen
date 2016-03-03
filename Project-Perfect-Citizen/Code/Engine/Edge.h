#ifndef EDGE_H
#define EDGE_H

#include <memory>
#include <string>
//#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>

namespace ppc {


class Edge {

private:

	int weight_;

	std::string relationship_;

	sf::Color color_;

	sf::FloatRect bounds_;

public:

	Edge();
	Edge(sf::Color);

	void setWeight(int);
	int getWeight() const;

	void setRelation(std::string);
	std::string getRelation() const;

	void setColorRed();
	void setColorGreen();
	void setColorBlack();
	sf::Color getColor() const;

	void setBounds(sf::FloatRect);
	sf::FloatRect getBounds();

	void constructBounds(sf::Vector2f,sf::Vector2f);

};


};  //End namespace mdg


#endif  //End EDGE_H
