#pragma once

//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
#define resourcePath() std::string("../Resources/")
#else
#include "ResourcePath.hpp"
#endif
///////////////////////////////////////////////////////////

