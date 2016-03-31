#include "Quitter.h"


using namespace ppc;

bool ppc::quitter = false;



void ppc::quitSection() {
    quitter = true;
}

