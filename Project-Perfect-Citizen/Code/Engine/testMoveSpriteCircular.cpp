
#include "testMoveSpriteCircular.h"

testMoveSpriteCircular::testMoveSpriteCircular() {
	this->sprite = new sf::Sprite();
	this->circleCenter = sf::Vector2f();
	this->degrees = 0;
	
}

testMoveSpriteCircular::testMoveSpriteCircular(sf::Sprite* sprt, sf::Vector2f c, float v) {

	this->sprite = sprt;
	this->circleCenter = c;
	this->degrees = v;
}

testMoveSpriteCircular::~testMoveSpriteCircular() {
	this->sprite = nullptr;
}

float testMoveSpriteCircular::distanceFormula(sf::Vector2f a, sf::Vector2f b) {
	float dx = pow(a.x - b.x,2.0f);
	float dy = pow(a.y - b.y, 2.0f);

	return sqrt(dx + dy);
}

void testMoveSpriteCircular::update(sf::Time deltaTime) {
	sf::Vector2f currPos = sprite->getPosition();
	sf::Vector2f currPosPrime;
	sf::Vector2f centerCircPrime = { 0,0 };
	sf::Vector2f newPos;

	float radius = distanceFormula(circleCenter, currPos);

	float currAngle; 
	float newAngle;  
	// NOTE : degree -> radians :- theta * (M_PI/180)

	//Step 1 - Center points around (0,0)
	currPosPrime = { currPos.x - circleCenter.x , currPos.y - circleCenter.y };


	currAngle = acos(currPosPrime.x / radius) * (180 / M_PI);
	newAngle = currAngle + degrees;
	if (newAngle > 360) newAngle -= 360;
	cout << currAngle << " " << newAngle << endl;
	if (newAngle < 180.f && newAngle >= 0.f) {
		newPos.x =  cos(newAngle * (M_PI / 180)) * radius;
		newPos.y =  sin((360 - newAngle) * (M_PI / 180)) * radius;
	} else {
		newPos.x = cos((newAngle) * (M_PI / 180)) * radius;
		newPos.y = sin((newAngle) * (M_PI / 180)) * radius;
	}

	cout << newPos.x << " " << newPos.y << endl;
	newPos += circleCenter;
	sprite->setPosition(newPos);
}