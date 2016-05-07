#include "NetworkInputCmpnt.h"
#include "../Engine/debug.h"
#include <cmath>
#include <cfloat>
#include "../Engine/DraggableInput.h"
const float MAX_DISTANCE_TO_EDGE = 10.f;

void ppc::NetworkInputCmpnt::selectEdge(sf::Vector2f mPos) {
	std::vector<std::pair<int, int>> edgeList;

	for (size_t i = 0; i < network_->size(); i++) {
		for (size_t j = i+1; j < network_->size(); j++) {
			if (network_->isAdjacent(i, j) &&
				network_->edge(i, j)->getBounds().contains(mPos)) {
				edgeList.push_back(std::make_pair(i, j));
			}
		}
	}

	std::pair<int, int> closest = { -1, -1 };
	float closestDist = FLT_MAX;
	for (size_t i = 0; i < edgeList.size(); ++i) {
		sf::Vector2f p1 = network_->vert(edgeList.at(i).first).getPosCenter();
		sf::Vector2f p2 = network_->vert(edgeList.at(i).second).getPosCenter();
		float dist = (abs((p2.y - p1.y) * mPos.x - (p2.x - p1.x) * mPos.y + p2.x*p1.y - p2.y*p1.x))/
			         (std::sqrtf(std::pow(p2.y - p1.y, 2) + std::pow(p2.x - p1.x, 2)));
		if (dist < closestDist && dist < MAX_DISTANCE_TO_EDGE) {
			closestDist = dist;
			closest = std::make_pair(edgeList.at(i).first, edgeList.at(i).second);
		}
	}
	if (closest != std::make_pair(-1, -1)) {
		sf::Color oldcolor;
		if (!(selectedEdge_.first == 0 && selectedEdge_.second == 0) &&
			network_->isAdjacent(selectedEdge_.first, selectedEdge_.second)) {
			unselectEdge(*network_->edge(selectedEdge_.second, selectedEdge_.first));
			unselectEdge(*network_->edge(selectedEdge_.first, selectedEdge_.second));
		}
		
		selectedEdge_ = closest;
		Edge* testedge = network_->edge(selectedEdge_.first, selectedEdge_.second);
		oldcolor = network_->edge(selectedEdge_.first, selectedEdge_.second)->getColor();
		if (oldcolor == sf::Color::Red) { 
			network_->edge(selectedEdge_.first, selectedEdge_.second)->setColorSelectedRed();
			network_->edge(selectedEdge_.second, selectedEdge_.first)->setColorSelectedRed();
		}
		else if (oldcolor == sf::Color::Green) {
			network_->edge(selectedEdge_.first, selectedEdge_.second)->setColorSelectedGreen();
			network_->edge(selectedEdge_.second, selectedEdge_.first)->setColorSelectedGreen();
		}
		else {
			network_->edge(selectedEdge_.first, selectedEdge_.second)->setColorSelectedBlack();
			network_->edge(selectedEdge_.second, selectedEdge_.first)->setColorSelectedBlack();
		}
		
		clickedEdge_ = true;
		clickedVert_ = false;

        //Create Event
        Event ev;
        ev.type = ev.NetworkType;
        ev.network.type = ev.network.Selected;
        ev.network.u = closest.first;
        ev.network.v = closest.second;
        ev.network.net = network_;
        network_->onManip().sendEvent(ev);

		return;
	}
}

void ppc::NetworkInputCmpnt::unselectEdge(Edge& e) {
	sf::Color oldcolor = e.getColor();
	if (oldcolor == selRed) e.setColorRed();
	else if (oldcolor == selGreen) e.setColorGreen();
	else if (oldcolor == selBlack) e.setColorBlack();
}

void ppc::NetworkInputCmpnt::selectVert(sf::Vector2f mPos) {
	network_->vert(selectedVert_).deselectVert();
	if (!(selectedEdge_.first == 0 && selectedEdge_.second == 0) && 
		network_->isAdjacent(selectedEdge_.first, selectedEdge_.second)) {
		unselectEdge(*network_->edge(selectedEdge_.first, selectedEdge_.second));
		unselectEdge(*network_->edge(selectedEdge_.second, selectedEdge_.first));
	}
	for (size_t i = 0; i < network_->size(); i++) {
		if (network_->vert(i).getLocalBounds().contains(mPos)) {
			selectedVert_ = i;
			network_->vert(selectedVert_).selectVert();
			clickedVert_ = true;
			clickedEdge_ = false;

            //Create Event
            Event ev;
            ev.type = ev.NetworkType;
            ev.network.type = ev.network.Selected;
            ev.network.u = i;
            ev.network.v = -1;
            ev.network.net = network_;
            network_->onManip().sendEvent(ev);

			updateDataText();
			return;
		}
	}
	clickedVert_ = false;
}

void ppc::NetworkInputCmpnt::loopEdgeColor() {
	Edge* e1 = network_->edge(selectedEdge_.first,
		selectedEdge_.second);

	Edge* e2 = network_->edge(selectedEdge_.second,
		selectedEdge_.first);

	if (e1->getColor() == selRed) {
		e1->setColorSelectedGreen();
		e2->setColorSelectedGreen();
	} else if (e1->getColor() == selGreen) {
		e1->setColorSelectedBlack();
		e2->setColorSelectedBlack();
	} else if (e1->getColor() == selBlack) {
		e1->setColorSelectedRed();
		e2->setColorSelectedRed();
	}

    Event ev;
    ev.type = ev.NetworkType;
    ev.network.type = ev.network.Edited;
    ev.network.u = selectedEdge_.first;
    ev.network.v = selectedEdge_.second;
    ev.network.net = network_;
    network_->onManip().sendEvent(ev);
}

void ppc::NetworkInputCmpnt::updateDataText() {
	if (pipeRender_ == nullptr) return;
	pipeRender_->clearString();
	for (unsigned int i = 0; i < solution_->size(); ++i) {
		if (solution_->isAdjacent(selectedVert_, i)) {
			std::vector<std::vector<std::string>> smsvec = 
				solution_->edge(selectedVert_, i)->getSmsData();

			for (unsigned int j = 0; j < smsvec.size(); ++j) {
				unsigned int charlimit = 32; // THIS SHOULD BE DYNAMIC BASED ON WINDOW AND FONT SIZE
				unsigned int currchars = 0;
				std::string buff = "";
				for (unsigned int k = 0; k < smsvec[j].size(); ++k) {
					if (smsvec[j][k] == "\n") {
						pipeRender_->appendString(buff + '\n');
						buff = "";
						currchars = 0;
						continue;
					}
					if (currchars + smsvec[j][k].size() < charlimit) {
						buff += smsvec[j][k] + ' ';
						currchars += smsvec[j][k].size() + 1;
					}
					else {
						pipeRender_->appendString(buff + '\n');
						buff = smsvec[j][k] + ' ';
						currchars = buff.size();
					}
				}
				if (currchars != 0) pipeRender_->appendString(buff + "\n\n");
				else pipeRender_->appendString("\n\n");
			}
		}
	}
}

ppc::NetworkInputCmpnt::NetworkInputCmpnt(Network& net,
	Network& sol, ppc::InputHandler& ih) : 
	InputComponent(3), network_(&net), solution_(&sol), handle_(ih)
{
	this->watch(handle_, sf::Event::KeyPressed);
	this->watch(handle_, sf::Event::MouseButtonPressed);
	this->watch(handle_, sf::Event::MouseButtonReleased);

	pipeRender_ = nullptr;

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

std::vector<ppc::DraggableInput*>* ppc::NetworkInputCmpnt::getDraggables() {
	return &drags_;
}

void ppc::NetworkInputCmpnt::setPipelineData(PipelineDataRenderComponent& pdrc) {
	pipeRender_ = &pdrc;
}

ppc::NetworkInputCmpnt::~NetworkInputCmpnt() {
	for (auto it = drags_.begin(); it != drags_.end(); ++it) {
		delete *it;
	}
}

bool ppc::NetworkInputCmpnt::registerInput(Event ppcEv) {
    sf::Event ev(ppcEv);
	sf::Vector2f mousePos(float(ev.mouseButton.x),
		float(ev.mouseButton.y));
	//If left click, select a vertex/edge
	if (ev.type == ev.MouseButtonPressed) {
		if (ev.mouseButton.button == sf::Mouse::Left) {
			selectVert(mousePos);
			if(clickedVert_ == false) selectEdge(mousePos);
		}
		//If right click
		else if (ev.mouseButton.button == sf::Mouse::Right) {
			if (clickedVert_ == true) {
				size_t temp = selectedVert_;
				selectVert(mousePos);
				if (selectedVert_ != temp && 
					!network_->isAdjacent(temp,selectedVert_)) 
				{
					Edge e;
					e.setWeight(0);
					e.setColorBlack();
					e.setRelation("");
					network_->setEdge(temp, selectedVert_, e);
					network_->setEdge(selectedVert_, temp, e);
				}
			}
		}
	} else if (ev.type == sf::Event::KeyPressed) {

		if (ev.key.code == sf::Keyboard::C && clickedVert_) {
			DEBUGF("ni", "HERE");
			if (network_->getCenter() != -1) 
				network_->vert(network_->getCenter()).setColor(sf::Color(180,180,180));
			network_->setCenter(selectedVert_);
			network_->vert(selectedVert_).setColor(sf::Color::Red);
			return false;
		}

		if (clickedEdge_ == false) {
			if (!(selectedEdge_.first == 0 && selectedEdge_.second == 0) &&
				network_->isAdjacent(selectedEdge_.first, selectedEdge_.second)) {
				unselectEdge(*network_->edge(selectedEdge_.first, selectedEdge_.second));
				unselectEdge(*network_->edge(selectedEdge_.second, selectedEdge_.first));
			}
			return false;
		}

		switch (ev.key.code) {

		case sf::Keyboard::Delete:
		case sf::Keyboard::Z:
			network_->removeEdge(selectedEdge_.first,
				selectedEdge_.second);
			network_->removeEdge(selectedEdge_.second,
				selectedEdge_.first);
			clickedEdge_ = false;
			break;
		case sf::Keyboard::Space:
			loopEdgeColor();
			break;
		case sf::Keyboard::A:
			network_->edge(selectedEdge_.first,
				selectedEdge_.second)->setColorSelectedBlack();
			network_->edge(selectedEdge_.second,
				selectedEdge_.first)->setColorSelectedBlack();
			break;
		case sf::Keyboard::S:
			network_->edge(selectedEdge_.first,
				selectedEdge_.second)->setColorSelectedRed();
			network_->edge(selectedEdge_.second,
				selectedEdge_.first)->setColorSelectedRed();
			break;
		case sf::Keyboard::D:
			network_->edge(selectedEdge_.first,
				selectedEdge_.second)->setColorSelectedGreen();
			network_->edge(selectedEdge_.second,
				selectedEdge_.first)->setColorSelectedGreen();
			break;
		}
	}

	return false;
}






void ppc::NetworkInputCmpnt::setClampBounds(const sf::FloatRect clampBounds) {
    for (ppc::DraggableInput* di : drags_) {
        di->setClampBounds(clampBounds);
    }
}




void ppc::NetworkInputCmpnt::unBoundDraggables() {
    for (ppc::DraggableInput* di : drags_) {
        di->removeClamp();
    }
}


