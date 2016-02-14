#pragma once

#include <iostream>
#include "desktop.h"

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief A Faux-Decorator that logs information for Desktops.
	///@details Normally, Decorators would handle the deletion of the
	/// object they are decoration, but this is ins't a real decorator
	/// deletion of desktops rely on the user instead of the
	/// decorator.
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class DesktopLogger {

	private:

		Desktop *loggedDesktop_;
		ostream& out_;

	public:

		DesktopLogger() = delete;
		DesktopLogger(Desktop&, ostream&);

		~DesktopLogger();

		void addWindow(WindowInterface*);
		void destroyWindow(WindowInterface*);
		void setStyle(OSStyle*);
		NodeState& getNodeState();
		void registerInput(sf::Event& ev);
		void update(sf::Time&);
		void refresh(sf::RenderStates states = sf::RenderStates());
	};
};
