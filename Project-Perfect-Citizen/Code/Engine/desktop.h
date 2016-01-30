//desktop.h
// Nader Sleem

#pragma once

#include <vector>

//temporary typedefs for classes/types not defined yet
typedef int operatingSys;
typedef char fileTree;
typedef long* window;

namespace ppc {
	//////////////////////////////////////////////////////////////////
	///@todo Connect this class with Window, 
	///opteratingSys (Operating System data structure), and
	///fileTree(data structure for "file trees")
	//////////////////////////////////////////////////////////////////
	class Desktop {

	private:
		operatingSys* os_;

		//Should we point to a file tree or contain an actual one?
		fileTree* ft_;

		using windVec = std::vector<window*>;
		windVec windows_;

	public:
		
		 Desktop();
		 Desktop(windVec windows, operatingSys &os, fileTree &ft);

		~Desktop();

		const operatingSys& getOS() const;
		const fileTree& getFileTree() const;

		//const window& getWindow(windVec::iterator it) const;
		
		windVec::iterator getIter(window* w);

		windVec::iterator windVecBegin();
		windVec::iterator windVecEnd();

		windVec::iterator addWindow(window* w);

		void removeWindow(window* w);
		void removeWindow(windVec::iterator it);

	};


};