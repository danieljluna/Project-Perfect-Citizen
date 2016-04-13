#include <iostream>
#include <vector>
#include "debug.h"
#include "BaseFileType.h"
#include "desktop.h"
#include "../../Code/Game/createWindow.h"

using namespace ppc;

BaseFileType::BaseFileType(ppc::FileType type)
{
	switch (type) {
	case FileType::Directory:
		this->filetype = ppc::FileType::Directory;
		break;
	case FileType::File:
		this->filetype = ppc::FileType::File;
		break;
	default:
		//throw std::exception("BaseFileType::BaseFiletype() :not a valid enum type");
		break;
	}
}

BaseFileType::~BaseFileType() {
    if (filetype == FileType::Directory) {
        //Remove Default Folders
        contents.erase(".");
        contents.erase("..");

        //Remove all other folders
        while (contents.size() > 0) {
            auto it = contents.begin();
            delete it->second;
            contents.erase(it);
        }
    }
}

void BaseFileType::uploadJson(std::string jString)
{
	this->jSonString = jString;
}

//void ppc::spawnFile(WindowInterface*& windowToModify, InputHandler & ih, NodeState & ns, sf::Image& buttonSheet, float x, float y, string p) {

void BaseFileType::readFile(ppc::Desktop& desk, sf::Image& im, std::string path)
{
	ppc::WindowInterface* FileWindow;
	if (this->encrypted) {
		return;
	}
	switch (this->filetype) {
	case FileType::File:
		FileWindow = new ppc::Window(500, 500, sf::Color(255, 255, 255));
		spawnFile(FileWindow, FileWindow->getInputHandler(), *desk.getNodeState(), im, 100, 200, path);
		desk.addWindow(FileWindow);
		std::cout << path << std::endl;
		break;
	case FileType::Directory:
		std::cout << "use CD instead" << endl;
		break;
	default:
		break;
	}
}

void BaseFileType::printDir()
{
	this->baseDirString = "";
	for (auto iter = this->contents.begin(); iter != this->contents.end(); iter++) {
		if (iter->second->hidden == true) {
			continue;	
		}
		std::cout << iter->first << std::endl;
		this->baseDirString += (iter->first + "@");
		std::cout << baseDirString << std::endl;
	}
}

void BaseFileType::makeFile(std::string filename, std::string content)
{
	//TODO: FIX MEMORY LEAKS!
    BaseFileType* newFile = new BaseFileType(ppc::FileType::File);
	newFile->fileData = content;
	this->contents[filename] = newFile;
}

BaseFileType* BaseFileType::makeDir(std::string filename)
{
    //TODO: FIX MEMORY LEAKS!
	BaseFileType* newDir = new BaseFileType(ppc::FileType::Directory);
	newDir->contents["."] = newDir;
	newDir->contents[".."] = this;
	this->contents[filename] = newDir;
	return newDir;
}

ppc::BaseFileType * ppc::BaseFileType::findElement(std::string filename)
{
	for (auto iter = this->contents.begin(); iter != this->contents.end(); iter++) {
		if (iter->first == filename) {
			return iter->second;
		}
	}
	return nullptr;
}

BaseFileType* BaseFileType::getParent()
{
	return this->findElement("..");
}

FileType BaseFileType::getFileType()
{
	return this->filetype;
}

void BaseFileType::setVisibility(bool flag)
{
	this->hidden = flag;
}

void BaseFileType::setEncryption(bool flag) {
	this->encrypted = flag;
}

bool BaseFileType::isHidden()
{
	return hidden;
}

bool BaseFileType::isEncrypted()
{
	return encrypted;
}

std::map<std::string, BaseFileType*> BaseFileType::getContents()
{
	return this->contents;
}

std::string BaseFileType::getFileData()
{
	return this->fileData;
}

void ppc::BaseFileType::setPassword(std::string pwd, std::string hint)
{
	password = pwd;
	passwordProtected = true;
	passwordHint = hint;
}

bool ppc::BaseFileType::comparePassword(std::string input)
{
	if (input == password) {
		passwordProtected = false;
		return true;
	}
	passwordAttemps++;
	if (passwordAttemps >= 2) {
		std::cout << passwordHint << std::endl;
	}
	return false;
}

bool ppc::BaseFileType::isPasswordProtected()
{
	if (passwordProtected) {
		return true;
	}
	return false;
}


