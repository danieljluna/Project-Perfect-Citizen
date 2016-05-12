#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

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
			DE0 = 0,
			DEPlayer,
			DE1,
			DE2A,
			DE2B,
			DE3,
            Count
        };

		enum FontList {
			//Fill with Enuns as Fonts are added
			Consola = 0,
			Micross,
			VT323Regular,
			FontCount
		};

		enum ReportType {
			A = 0, //guilty1
			B, //guilty2
			C, //not guilty1
			D // not guilty2
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

		static void setCurrDesktopEnum(DesktopList);

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

		static ReportType getCurrReportType();
		static void setCurrReportType(ReportType);

		///////////////////////////////////////////////////////////////
		///@brief Returns the sf:Font of the given Font
		///////////////////////////////////////////////////////////////
		static sf::Font& getFont(FontList f);

		static std::string getReportFile();

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

    private:

        static sf::RenderWindow* screen_;
        static ppc::Desktop* currDesktop_;

		static DesktopList currDesktopEnum_;
		static ReportType currReportType_;

        static bool quitter_;

        static std::map<DesktopList, std::string> desktopFileMap_;

		static std::map<FontList, sf::Font> fontMap_;

		static std::map <std::pair<DesktopList,ReportType>, std::string > reportListMap_;

		static bool isLoading_;

		static sf::RectangleShape tempLoadScreen_;
        
        static sf::Image loadImage_;
        
        static sf::Texture loadTexture_;
        
        static sf::Sprite loadBar_;
        
        static sf::Sprite loadBarBorder_;
        
        static sf::Sprite loadingDecal_;

		static sf::RectangleShape tempLoadBar_;

	};
};