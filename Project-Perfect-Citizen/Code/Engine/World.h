#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Setting.h"


namespace ppc {

	class Desktop;

	///////////////////////////////////////////////////////////////////
	///@brief Class that handles Level transitions, saving/loading, etc
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class World {
    public:

        enum DesktopList {
            //Fill with Enums as input files are made
            DesktopCount
        };

		enum FontList {
			//Fill with Enuns as Fonts are added
			Consola = 0,
			Micross,
			VT323Regular,
			FontCount
		};

		enum ReportList {
			DE1A = 0, //Guilty
			DE1B, //NOT Guilty
			DE2,
			DE3
		};

		///////////////////////////////////////////////////////////////
		// Ctors
		///////////////////////////////////////////////////////////////
		World() = delete;

      /////////////////////////////////////////////////////////////////
      // Setters
      /////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		///@brief Set the screen the game is played on.
		///@param [in] sf::RenderWindow
		///////////////////////////////////////////////////////////////
		static void setGameScreen(sf::RenderWindow&);

        ///////////////////////////////////////////////////////////////
		///@brief Set the Desktop currently used by World
		///////////////////////////////////////////////////////////////
		static void setCurrDesktop(ppc::Desktop&);

		///////////////////////////////////////////////////////////////
		///@brief Returns a pointer to the Game Screen
		///////////////////////////////////////////////////////////////
		static sf::RenderWindow& getGameScreen();

		///////////////////////////////////////////////////////////////
		///@brief Returns a pointer to the Current Desktop
		///////////////////////////////////////////////////////////////
		static Desktop& getCurrDesktop();

		///////////////////////////////////////////////////////////////
		// Desktop Manipulation
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		///@brief Runs the main game loop with the given Desktop
		///////////////////////////////////////////////////////////////
		static bool runDesktop(ppc::Desktop&);

        static bool loadDesktop(DesktopList desk);

        ///////////////////////////////////////////////////////////////
        ///@brief Loads in a Desktop from a file to the World
        ///@details The imported Desktop becomes the new current 
        /// Desktop, while the old one (if there was one) is destroyed.
        ///////////////////////////////////////////////////////////////
        static bool loadDesktop(std::string filename);

		///////////////////////////////////////////////////////////////
		///@brief Initializes the fontMap of the World
		///////////////////////////////////////////////////////////////
		static void initFontMap();

		///////////////////////////////////////////////////////////////
		///@brief Returns the sf:Font of the given Font
		///////////////////////////////////////////////////////////////
		static sf::Font& getFont(FontList f);

		static std::string getReportFile(ReportList rl);

        static void restartDesktop();

        static void quitDesktop();

		///////////////////////////////////////////////////////////////
		///@brief Runs the main game loop with the current Desktop
		///////////////////////////////////////////////////////////////
		static bool runCurrDesktop();

		//////////////////////////////////////////////////////////////
		// Loading Screen Functions
		//////////////////////////////////////////////////////////////

		static void initLoadScreen();

		static void startLoading();

        static bool isLoading() { return isLoading_; };

		static void setLoading(float);

		static void drawLoading();

		static void endLoading();

        static void loadState(std::string filename);

        static void saveState(std::string filename);

    private:

        enum savGroups {
            SettingsTag = 0,
            StateTag,
            SaveTagCount
        };

        static sf::RenderWindow* screen_;
        static ppc::Desktop* currDesktop_;

        static bool quitter_;

        static std::map<DesktopList, std::string> desktopFileMap_;

		static std::map<FontList, sf::Font> fontMap_;

		static std::map<ReportList, std::string> reportListMap_;

		static bool isLoading_;

		static sf::RectangleShape tempLoadScreen_;
        
        static sf::Image loadImage_;
        
        static sf::Texture loadTexture_;
        
        static sf::Sprite loadBar_;
        
        static sf::Sprite loadBarBorder_;
        
        static sf::Sprite loadingDecal_;

		static sf::RectangleShape tempLoadBar_;

        static Setting settings_;

        static std::map<std::string, savGroups> saveGroupMap_;

	};
};