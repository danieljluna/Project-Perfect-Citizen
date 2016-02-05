#pragma once
#include "TreeNode.h"
#include <iostream>
#include <vector>;

using namespace std;
namespace ppc {
	class NodeState {
		friend class TreeNode;
	private:
		TreeNode* root;
		TreeNode* cwd;
		vector<string> workingDirectory;
	public:
		void popWorking();
		void pushWorking(string filename);
		void printWorking();
	};
}