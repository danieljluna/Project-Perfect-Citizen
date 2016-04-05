#pragma once
#include <SFML/Window/Event.hpp>


namespace ppc {

//Flag that should be tested to see if we want to quit the current 
//  section
extern bool quitter;

///////////////////////////////////////////////////////////////////////
/// @brief Used to quit the current Desktop and move to the next.
/// @details This functionality will eventually be pushed to the World
///     class.
///////////////////////////////////////////////////////////////////////
void quitSection();

};
