#pragma once

#include <iostream>
#include "desktop.h"

namespace ppc {

	class DesktopLogger {

	private:

		Desktop *loggedDesktop;
		ostream& out;

	public:

		DesktopLogger() = delete;
		DesktopLogger(Desktop&, ostream&);

		~DesktopLogger();

		void addWindow(WindowInterface*);
		void destroyWindow(WindowInterface*);
		void setStyle(OSStyle*);
		FileState& getRoot();
		void registerInput(sf::Event& ev);
		void update(sf::Time&);
		void refresh(sf::RenderStates states = sf::RenderStates());
	};
};
