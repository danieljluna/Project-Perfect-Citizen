#include "ppc_component.h"

//initialization fuckery. You need this line to instantiate a static vector.  
//If you dont have this line you'll get a unresolved external symbol error
//see http://stackoverflow.com/questions/7531981/how-to-instantiate-a-static-vector-of-object
std::vector<sf::Sprite*> Component::renderVector;