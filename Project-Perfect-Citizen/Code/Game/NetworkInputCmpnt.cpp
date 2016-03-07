#include "NetworkInputCmpnt.h"
#include "../Engine/debug.h"

void ppc::NetworkInputCmpnt::selectEdge(sf::Vector2f mPos) {
	for (size_t i = 0; i < network_->size(); i++) {
		for (size_t j = 0; j < network_->size(); j++) {
			if (network_->edge(i, j) != nullptr &&
				network_->edge(i, j)->getBounds().contains(mPos)) {
				selectedEdge_ = { i,j };
				clickedEdge_ = true;
				return;
			}
		}
	}
	clickedEdge_ = false;
}

void ppc::NetworkInputCmpnt::selectVert(sf::Vector2f mPos) {
	for (size_t i = 0; i < network_->size(); i++) {
		if (network_->vert(i).getLocalBounds().contains(mPos)) {
			selectedVert_ = i;
			clickedVert_ = true;
			return;
		}
	}
	clickedVert_ = false;
}

void ppc::NetworkInputCmpnt::loopEdgeColor() {
	Edge* e = network_->edge(selectedEdge_.first,
		selectedEdge_.second);
	if (e->getColor() == sf::Color::Red) {
		e->setColorGreen();
	} else if (e->getColor() == sf::Color::Green) {
		e->setColorBlack();
	} else if (e->getColor() == sf::Color::Black) {
		e->setColorRed();
	}
}

ppc::NetworkInputCmpnt::NetworkInputCmpnt(Network& n,
	ppc::InputHandler& ih) : 
	InputComponent(3), network_(&n), handle_(ih)
{
	this->watch(handle_, sf::Event::KeyPressed);
	this->watch(handle_, sf::Event::MouseButtonPressed);
	this->watch(handle_, sf::Event::MouseButtonReleased);

	clickedVert_ = false;
	clickedEdge_ = false;
	selectedVert_ = 0;
	selectedEdge_ = { 0,0 };

	//Make every vertex draggable
	for (size_t i = 0; i < network_->size(); i++) {
		DraggableInput* dI = new DraggableInput(network_->vert(i));
		network_->vert(i).applyDraggable(*dI, handle_);
		dI->setBounds(network_->vert(i).getLocalBounds());
		drags_.push_back(dI);
	}

}

vector<ppc::DraggableInput*>* ppc::NetworkInputCmpnt::getDraggables() {
	return &drags_;
}

ppc::NetworkInputCmpnt::~NetworkInputCmpnt() {
	for (auto it = drags_.begin(); it != drags_.end(); ++it) {
		delete *it;
	}
}

bool ppc::NetworkInputCmpnt::registerInput(sf::Event& ev) {
	sf::Vector2f mousePos(float(ev.mouseButton.x),
		float(ev.mouseButton.y));
	//If left click, select an edge
	if (ev.type == ev.MouseButtonPressed) {
		if (ev.mouseButton.button == sf::Mouse::Left) {
			selectEdge(mousePos);
		}
		//If right click, select a vertex
		else if (ev.mouseButton.button == sf::Mouse::Right) {
			if (clickedVert_ == false) {
				selectVert(mousePos);
			} else {
				size_t temp = selectedVert_;
				selectVert(mousePos);
				if (selectedVert_ != temp && 
					!network_->isAdjacent(temp,selectedVert_)) 
				{
					Edge e;
					e.setWeight(0);
					e.setColorRed();
					e.setRelation("");
					network_->setEdge(temp, selectedVert_, e);
					clickedVert_ = false;
				}
			}
		}
	} else if (ev.type == sf::Event::KeyPressed) {
		if (clickedEdge_ == false) return false;

		switch (ev.key.code) {

		case sf::Keyboard::Delete: 
			network_->removeEdge(selectedEdge_.first, 
				selectedEdge_.second);
			clickedEdge_ = false;
			break;
		case sf::Keyboard::Space:
			loopEdgeColor();
			break;
		case sf::Keyboard::Z:
			network_->edge(selectedEdge_.first,
				selectedEdge_.second)->setColorBlack();
			break;
		case sf::Keyboard::X:
			network_->edge(selectedEdge_.first,
				selectedEdge_.second)->setColorRed();
			break;
		case sf::Keyboard::C:
			network_->edge(selectedEdge_.first,
				selectedEdge_.second)->setColorGreen();
			break;
		}
	}

	return false;
}
