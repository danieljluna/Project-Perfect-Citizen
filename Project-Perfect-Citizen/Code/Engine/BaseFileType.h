#pragma once
//implemented by Andy
#include <iostream>
#include <vector>
#include <map>
#include <String>
//using namespace std;

namespace ppc {
	enum FileType { Directory, File};
	///////////////////////////////////////////////
	///@brief BaseFileType represents the nodes
	///of file tree. By default, these nodes can
	///be of type file (a text file) or directory
	///FileType can also be a base class. The
	///purpose of this is to implment your own 
	///version of readFile() or any of the other
	///functions. You can use its base functionality
	///as the functions do not force you to implement 
	///them in child classes. I recommend redefining 
	///readFile to suit your Json however. 
	///////////////////////////////////////////////
	class BaseFileType {
		friend class NodeState;
	protected:
		///////////////////////////////////////////////
		///@brief BaseFileType constructor.
		///@param type is of type FileType which is an
		///enum at the top of this page. The enum tells
		///tree what kind of node it is. As its core, 
		///the node can either be a plain file or a
		///Directory;
		///////////////////////////////////////////////
		BaseFileType(ppc::FileType type);
		///////////////////////////////////////////////
		///@brief data for text files
		///////////////////////////////////////////////
		std::string data = "";
		///////////////////////////////////////////////
		///@brief JSon string for the specific node
		///////////////////////////////////////////////
		std::string jSonString = "";
		///////////////////////////////////////////////
		///@brief Map of strings and BaseFileType pointers
		///Only used if the file is a Directory;
		///////////////////////////////////////////////
		std::map<std::string, BaseFileType*> contents;
		///////////////////////////////////////////////
		///@brief Type of file. At its base implementation
		///it can either be a fileType::Directory or
		///FileType::File
		///////////////////////////////////////////////
		ppc::FileType filetype;
	public:
		///////////////////////////////////////////////
		///@brief assigns Json string to jSonString;
		///@param jString. String loaded from
		///Json file.
		///////////////////////////////////////////////
		virtual void uploadJson(std::string jString);
		///////////////////////////////////////////////
		///@brief Prints the data from a text file
		///Returns if the target isnt a file. 
		///////////////////////////////////////////////
		virtual void readFile();
		///////////////////////////////////////////////
		///@brief Prints the directory of the node. 
		///////////////////////////////////////////////
		virtual void printDir();
		///////////////////////////////////////////////
		///@brief creates a plain text file
		///@param filename: name of the new File
		///@param content: data content of the new
		///file. 
		///////////////////////////////////////////////
		virtual void makeFile(std::string filename, std::string content);
		///////////////////////////////////////////////
		///@brief Creates a new Directory in the node
		///@param filename: name of new Directory
		///////////////////////////////////////////////
		virtual BaseFileType* makeDir(std::string filename);
		///////////////////////////////////////////////
		///@brief Checks if the element is within the 
		///directory and returns the element if it exists;
		///returns null if it doesnt exist. 
		///@param filename: name of chosen element
		///////////////////////////////////////////////
		virtual BaseFileType* findElement(std::string filename);
		///////////////////////////////////////////////
		///@brief Returns the parent of the inode. 
		///////////////////////////////////////////////
		virtual BaseFileType* getParent();
		///////////////////////////////////////////////
		///@brief Returns the enum type of the node.
		///////////////////////////////////////////////
		virtual ppc::FileType getFileType();
	};
};
