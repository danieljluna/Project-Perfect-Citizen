#pragma once
//implemented by Andy
#include <iostream>
#include <vector>
#include <map>
#include <String>
//using namespace std;

namespace ppc {
	enum FileType { Directory, File};

	class BaseFileType {
		friend class NodeState;
	protected:
		BaseFileType(ppc::FileType type);
		std::string data = "";
		std::string jSonString = "";
		std::map<std::string, BaseFileType*> contents;
		ppc::FileType filetype;
	public:
		virtual void uploadJson(std::string jString);
		virtual void readFile();
		virtual void printDir();
		virtual void makeFile(std::string filename, std::string content);
		virtual BaseFileType* makeDir(std::string filename);
		virtual BaseFileType* findElement(std::string filename);
	};
};
