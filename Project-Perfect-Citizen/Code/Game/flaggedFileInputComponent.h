#pragma once

#include "../Engine/inputComponent.h"
#include "../Engine/desktop.h"
#include "../Engine/WindowInterface.h"
#include "../Engine/NodeState.h"
#include <iostream>

namespace ppc {

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated input component for explorer files
	/// @author Alex Vincent 
	/// @details Functionality: when clicked opens the corresponding file 
	///////////////////////////////////////////////////////////////////////
	class flaggedFileInputComponent : public ppc::InputComponent {

	private:

		Desktop* theDesktop_;
		WindowInterface* containingWindow;
		std::string fileName;
	

	public:

		flaggedFileInputComponent() = delete;
		virtual ~flaggedFileInputComponent();
		///////////////////////////////////////////////////////////////////////
		///@brief Ctor
		///////////////////////////////////////////////////////////////////////
		flaggedFileInputComponent(Desktop* dt, WindowInterface* cW, ppc::InputHandler& ih, std::string directoryName);

		Desktop* getDesktop();

		std::string getFileName();

		virtual bool registerInput(Event ev) override;

		virtual void recieveMessage(Event ev) override;


	};

	bool unflag_file(flaggedFileInputComponent*, ppc::Event);

	bool clear_flagged_files(Desktop*, ppc::Event);


};
