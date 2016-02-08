#pragma once
#include <iostream>
#include <vector>
#include "baseFileType.h"

using namespace std;
///////////////////////////////////////////////
///Class node state is a class used to monitor
///a single tree. It contains links to the 
///root of the tree along with the current
///mode of the tree (CWD). The nodeState
///class also holds a vector used to keep
///track of the CWD as well. This vector
///is updated when CDing around the tree
///////////////////////////////////////////////
namespace ppc {
	class NodeState {
		friend class BaseFileType;
	private:
		///////////////////////////////////////////////
		///@brief pointer to root of file tree
		///////////////////////////////////////////////
		BaseFileType* root;
		///////////////////////////////////////////////
		///@brief pointer to cwd of file tree
		///////////////////////////////////////////////
		BaseFileType* cwd;
		///////////////////////////////////////////////
		///@brief vector of strings that keeps track of
		///the current working directory
		///////////////////////////////////////////////
		vector<string> workingDirectory;
	public:
		///////////////////////////////////////////////
		///@brief pops off the last element in the
		///workingDirectory vector. Primarily used 
		///when dealing with changing directories. 
		///////////////////////////////////////////////
		void popWorking();
		///////////////////////////////////////////////
		///@brief calls push_back() on workingDirectory
		///with string param
		///@param Filename is the name of the directory
		///Do not imput a filePath, only a directory
		///name
		///////////////////////////////////////////////
		void pushWorking(string filename);
		///////////////////////////////////////////////
		///@brief Prints the current working directory
		/// "/" is considered root. 
		///////////////////////////////////////////////
		void printWorking();
		///////////////////////////////////////////////
		///@brief sets up the root of the file tree
		///must be called as soon as Node state is
		///created
		///@Sets up the root directory. Sets CWD to root
		///sets root to itself; Adds . and .. to the root
		///directory
		///////////////////////////////////////////////
		void setUp();
		///////////////////////////////////////////////
		///@brief assigns a BaseFileType node to the CWD
		///@param NewCwd is the new BaseFileType to become
		///CWD. Eror if the BaseFileType is not of 
		///ppc::FileType::Directory
		///////////////////////////////////////////////
		void setCwd(BaseFileType* newCwd);
		///////////////////////////////////////////////
		///@brief returns the CWD;
		///////////////////////////////////////////////
		BaseFileType* getCwd();
		///////////////////////////////////////////////
		///@brief returns the root;
		///////////////////////////////////////////////
		BaseFileType* getRoot();
		///////////////////////////////////////////////
		///@brief sets the CWD to Root, resets the 
		///working directory to its starting state
		///containing only "/"
		///////////////////////////////////////////////
		void moveToRoot();
	};
}//end ppc namespace