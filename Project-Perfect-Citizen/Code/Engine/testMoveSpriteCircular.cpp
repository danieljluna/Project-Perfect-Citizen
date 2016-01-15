
#include "testMoveSpriteCircular.h"

testMoveSpriteCircular::testMoveSpriteCircular() {
	this->sprite = new sf::Sprite();
	this->circleCenter = sf::Vector2f();
	this->angularVelocity = 0;
	
}

testMoveSpriteCircular::testMoveSpriteCircular(sf::Sprite* sprt, sf::Vector2f c, float v) {
	this->sprite = sprt;
	this->circleCenter = c;
	this->angularVelocity = v;
}

testMoveSpriteCircular::~testMoveSpriteCircular() {
	delete (sprite);
}

float testMoveSpriteCircular::distanceFormula(sf::Vector2f a, sf::Vector2f b) {
	float dx = pow(a.x - b.x,2.0f);
	float dy = pow(a.y - b.y, 2.0f);

	return sqrt(dx + dy);
}

void testMoveSpriteCircular::update(sf::Time deltaTime) {
	cout << "HERE@" << endl;
	sf::Vector2f currPos = sprite->getPosition();
	sf::Vector2f newPos;

	float radius = distanceFormula(circleCenter, currPos);
	float currAngle; 
	float newAngle;  // degree -> radians :- theta * (M_PI/180)

	currAngle = asin((currPos.y / radius) * (M_PI / 180.0f));
	newAngle = currAngle + 
		((angularVelocity*deltaTime.asSeconds()) * (M_PI / 180.0f));

	newPos.x = circleCenter.x + cos(newAngle)*radius;
	newPos.y = circleCenter.y + sin(newAngle)*radius;
	cout << newPos.x << endl;
	cout << newPos.y << endl;
	sprite->setPosition(newPos);

}