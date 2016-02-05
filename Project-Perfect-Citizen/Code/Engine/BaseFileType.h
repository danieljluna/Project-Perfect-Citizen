#pragma once
//implemented by Andy
#include <iostream>
#include <vector>
#include <map>
using namespace std;

namespace ppc {
	enum FileType { Directory, File};

	class BaseFileType {
		friend class NodeState;
	protected:
		BaseFileType();
		string data = "";
		map<string, BaseFileType*> contents;
	public:
		virtual void readFile();
		virtual void printDir();
	};
};
