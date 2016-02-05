#pragma once
//#include "TreeNode.h"
#include <iostream>
#include <vector>;
#include "baseFileType.h"

using namespace std;
namespace ppc {
	class NodeState {
		friend class BaseFileType;
	private:
		BaseFileType* root;
		BaseFileType* cwd;
		vector<string> workingDirectory;
	public:
		void popWorking();
		void pushWorking(string filename);
		void printWorking();
		void setUp();
		BaseFileType* getCwd();
		BaseFileType* getRoot();
	};
}