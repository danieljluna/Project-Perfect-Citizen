#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Setting.h"
#include <vector>
#include <utility>
#include "LevelPacket.h"
#include "Audio/AudioQueue.h"

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
			DELogo = 0,
			DEOpening,
			DELogin,
			DE0A,
			DE0B,
			DEPlayer1,
			DE1,
			DEPlayer2A,
			DE2A,
			DEPlayer2B,
			DE2B,
			DEPlayer3A,
			DEPlayer3B,
			DE3,
			DEEnd,
            DesktopCount
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

		///////////////////////////////////////////////////////////////
		// World std::Maps
		///////////////////////////////////////////////////////////////
		static std::map<DesktopList, std::string> desktopFileMap_;

		static std::map<DesktopList, ppc::LevelPacket> levelMap_;
		static void initLevelMap();
		static void setLevel(int, int);

		/////////////////////////////////////////////////////////////
		///@brief Signifies to the World that the next level to be
		/// loaded is a previous level
		/////////////////////////////////////////////////////////////
		static void goBack();

		using desktopLoaders = void(*)(ppc::Desktop&);

		static std::map<DesktopList, desktopLoaders> loaderMap_;
      /////////////////////////////////////////////////////////////////
      // Setters
      /////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		///@brief Set the screen the game is played on.
		///@param [in] sf::RenderWindow
		///////////////////////////////////////////////////////////////
		static void setGameScreen(sf::RenderWindow&);

        static sf::VideoMode getVideoMode();

        ///////////////////////////////////////////////////////////////
		///@brief Set the Desktop currently used by World
		///////////////////////////////////////////////////////////////
		static void setCurrDesktop(ppc::Desktop&);

		static void setCurrDesktopEnum(DesktopList);
		static DesktopList getCurrDesktopEnum();
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
		static void runDesktop();

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
		static std::string getBossEmail();

        static void restartDesktop();

        static void quitDesktop();

		///////////////////////////////////////////////////////////////
		///@brief Runs the main game loop with the current Desktop
		///////////////////////////////////////////////////////////////
		static int runCurrDesktop();

		//////////////////////////////////////////////////////////////
		// Loading Screen Functions
		//////////////////////////////////////////////////////////////

		static void initLoadScreen();

		static void startLoading();

        static bool isLoading() { return isLoading_; };

		static void setLoading(float);

		static void drawLoading();

		static void endLoading();

      /////////////////////////////////////////////////////////////////
      // Settings Functionality
      /////////////////////////////////////////////////////////////////

        static void setSettings(Setting settings);

        static Setting getSettings();

        static void loadState(std::string filename);

        static void saveState(std::string filename);

		static ppc::AudioQueue& getAudio();
		/////////////////////////////////////////////////////////////////
		// Loading Address Map
		/////////////////////////////////////////////////////////////////

		static std::string getCurrAddress();

		static std::string getAddress(DesktopList);
		
		static void setAddress(World::DesktopList, std::string);

		static void setCurrAddress(std::string);

		static void initAddressMap();

    private:

      /////////////////////////////////////////////////////////////////
      // Private Helpers
      /////////////////////////////////////////////////////////////////

        static void manifestSettings();

        static void drawDesktop();

		static void registerInput();

		static void update(sf::Clock&, sf::Time&);

        static void initializeResolution();

      /////////////////////////////////////////////////////////////////
      // Private Vars / Enums
      /////////////////////////////////////////////////////////////////

        enum savGroups {
            SettingsTag = 0,
            StateTag,
            SaveTagCount
        };

        static sf::RenderWindow* screen_;
        static ppc::Desktop* currDesktop_;

		static DesktopList currDesktopEnum_;
		static ReportType currReportType_;

		static bool progToNext_
			;
        static bool quitter_;

		static std::map<FontList, sf::Font> fontMap_;

		static std::map <std::pair<DesktopList, ReportType>, std::string > reportListMap_;

		static std::map <std::pair<DesktopList, ReportType>, std::string > bossEmailMap_;

		static std::map <World::DesktopList, std::string> loadingAddressMap_;

		static bool isLoading_;

		static bool isLoadBarFull_;

		static sf::RectangleShape tempLoadScreen_;
        
        static sf::Image loadImage_;
        
        static sf::Texture loadTexture_;
        
        static sf::Sprite loadBar_;
        
        static sf::Sprite loadBarBorder_;
        
        static sf::Sprite loadingDecal_;
        
        static sf::Text loadingAddress_;
        
        static sf::Sprite clickToContinue_;

		static sf::RectangleShape tempLoadBar_;

        static sf::RectangleShape blackBars_[2];

        static Setting settings_;
        
        static std::map<std::string, savGroups> saveGroupMap_;

        static sf::Transform worldTransform_;

		static ppc::AudioQueue audio_;
	};
};