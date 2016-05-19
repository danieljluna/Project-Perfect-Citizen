#pragma once

namespace sf {
    class Image;
};

namespace ppc {
    class Desktop;
    class WindowInterface;
    class InputHandler;
};


///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that sets up complete desktops
/// @author Alex Vincent 
/// @details Create a desktop reference (statically or dynamically) and
/// pass it by reference to any one of these functions. The passed entity 
/// will be augmented by the function you called on it.
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
///@brief Constructs the entire player's desktop with icons.
///
///@param The newly created desktop to add components/entities to.
///@param A reference to the desktop's window interface
///@param A reference to the desktop's window interface's input handler
///@param A sprite sheet from which to read the icon images
///@param A sprite sheet from which to read the button images
///////////////////////////////////////////////////////////////////////
void createLoginDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet);

void createPlayerDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet);

void createTeacherDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet);

void createDummyDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet);

void createArtistDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet);

void createPoliticianDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet);

void createTrailerDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet);
