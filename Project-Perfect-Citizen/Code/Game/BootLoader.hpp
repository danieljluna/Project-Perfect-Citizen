
#ifndef BootLoader_hpp
#define BootLoader_hpp

#include <stdio.h>
#include <string>



///////////////////////////////////////////////////////////////////////
/// @brief Boot Loader animation sequence displayed at start of game
/// @author Micahel Lowe
/// @details This is intended to be somewhat temporary. Eventually
///          The boot loader will be its own desktop.
///////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
/// @brief creates random strings for the file paths
/// @param stringLength is the desired length of the string
////////////////////////////////////////////////////////////////////
std::string getRandomString(int stringLength);

////////////////////////////////////////////////////////////////////
/// @brief Performs the actual sequence of loading text into the
///         String to be drawn.
/// @param step indicates how many frame refreshes have passed
/// @param renderString is the string to be updated and returned
////////////////////////////////////////////////////////////////////
std::string bootLoad(int step, std::string renderString);

#endif /* BootLoader_hpp */
