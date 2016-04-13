#pragma once
//implemented by Andy
#include <map>
#include <String>
#include "subject.h"

namespace sf {
    class Image;
};

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
	class Desktop;
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
        /// @brief Virtual Destructor
        ///////////////////////////////////////////////
        virtual ~BaseFileType();

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
		///////////////////////////////////////////////
		///@brief Dictates whether or nto file is
		///visable
		///////////////////////////////////////////////
		bool hidden = false;
		///////////////////////////////////////////////
		///@brief Dictates whether or not file is 
		///encrypted
		///////////////////////////////////////////////		
		bool encrypted = false;
		//////////////////////////////////////////////
		///@brief string representation of what
		///ls will output
		//////////////////////////////////////////////
		std::string baseDirString = "";
		ppc::Subject* fileSubject = nullptr;
		//////////////////////////////////////////////
		///@brief has the file ever been opened?
		//////////////////////////////////////////////
		bool sealed = true;
		std::string fileData = "";
		bool passwordProtected = false;
		std::string password = "";
		int passwordAttemps = 0;
		std::string passwordHint = "";

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
		virtual void readFile(Desktop& desk, sf::Image& im, std::string path);
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
		///////////////////////////////////////////////
		///@brief sets the visibility to the flag
		///specified
		///////////////////////////////////////////////
		virtual void setVisibility(bool flag);
		///////////////////////////////////////////////
		///@brief sets the encryption to the flag
		///specified
		///////////////////////////////////////////////
		virtual void setEncryption(bool flag);
		///////////////////////////////////////////////
		///@brief returns the status of BaseFileType::hidden
		///////////////////////////////////////////////
		virtual bool isHidden();
		///////////////////////////////////////////////
		///@brief returns the status of BaseFileType::encrypted
		///////////////////////////////////////////////
		virtual bool isEncrypted();
		
		virtual std::map<std::string, BaseFileType*> getContents();

		virtual ppc::Subject* getSubject() { return fileSubject; };

		virtual std::string getFileData();

		virtual void setPassword(std::string pwd, std::string hint);

		virtual bool comparePassword(std::string input);

		virtual bool isPasswordProtected();
		//virtual void addFileObserver(sf::Event& ev, bool(*obFunction)(T*, sf::Event&);
	};
};
