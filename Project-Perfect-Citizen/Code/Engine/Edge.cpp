#include "Edge.h"

using namespace ppc;

ppc::Edge::Edge() {
	weight_ = 0;
	relationship_ = "";
	color_ = sf::Color::Black;
	bounds_ = sf::FloatRect();
}

void ppc::Edge::setWeight(int i = 0) {
	weight_ = i;
}

int ppc::Edge::getWeight() const {
	return weight_;
}

void ppc::Edge::setRelation(std::string s) {
	relationship_ = s;
}

std::string ppc::Edge::getRelation() const {
	return relationship_;
}

void ppc::Edge::setColorRed() {
	color_ = sf::Color::Red;
}

void ppc::Edge::setColorGreen() {
	color_ = sf::Color::Green;
}

void ppc::Edge::setColorBlack() {
	color_ = sf::Color::Black;
}

sf::Color ppc::Edge::getColor() const {
	return color_;
}

void ppc::Edge::setBounds(sf::FloatRect rect) {
	bounds_ = rect;
}

sf::FloatRect ppc::Edge::getBounds() {
	return bounds_;
}

void ppc::Edge::constructBounds(sf::Vector2f p1, sf::Vector2f p2) {
	if (p1.x < p2.x) {
		bounds_.left = p1.x;
		bounds_.width = p2.x - p1.x;
	} else {
		bounds_.left = p2.x;
		bounds_.width = p1.x - p2.x;
	}

	if (bounds_.width < minWidth_) {
		bounds_.left -= minWidth_/2;
		bounds_.width = minWidth_;
	}

	if (p1.y < p2.y) {
		bounds_.top = p1.y;
		bounds_.height = p2.y - p1.y;
	} else {
		bounds_.top = p2.y;
		bounds_.height = p1.y - p2.y;
	}

	if (bounds_.height < minHeight_) {
		bounds_.top -= minHeight_/2.f;
		bounds_.height = minHeight_;
	}
}

void Edge::pushSmsData(const std::vector<std::string>& data) {
	smsData_.push_back(data);
}

std::vector<std::vector<std::string>> Edge::getSmsData() {
	return smsData_;
}


