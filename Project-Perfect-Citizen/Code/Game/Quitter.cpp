#include "Quitter.h"


using namespace ppc;

bool ppc::quitter = false;



bool ppc::quitSection(int* a, sf::Event& ev) {
    quitter = true;
    return true;
}

