#include <iostream>
#include <vector>
#include "debug.h"
#include "BaseFileType.h"
#include "desktop.h"
#include "../Game/createWindow.h"
#include <stdio.h>
#include <ctype.h>
#include "World.h"
#include "Window.h"

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

ppc::BaseFileType::BaseFileType(std::string test)
{
	if (test == "Directory" || test == "directory") {
		this->filetype = ppc::FileType::Directory;
		return;
	}
	else if (test == "file" || test == "File") {
		this->filetype = ppc::FileType::File;
		return;
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
	} else {
		contents.clear();
	}
}

void ppc::BaseFileType::setName(std::string newName)
{
	this->name = newName;
}

void BaseFileType::uploadJson(std::string jString)
{
	this->jSonString = jString;
}

void BaseFileType::readFile(std::string filename, std::string path)
{
	ppc::WindowInterface* FileWindow;
	if (this->encrypted) {
		return;
	}
	switch (this->filetype) {
	case FileType::File:
		FileWindow = new ppc::Window(500, 500, sf::Color(255, 255, 255));
		spawnFile(FileWindow, FileWindow->getInputHandler(), static_cast<float>(rand() % 500 + 25), static_cast<float>(rand() % 400 + 25), filename, path);
		World::getCurrDesktop().addWindow(FileWindow);
		std::cout << path << std::endl;
		break;
	case FileType::Directory:
		std::cout << "use CD instead" << std::endl;
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
    newFile->name = filename;
	this->contents[filename] = newFile;
}

BaseFileType* BaseFileType::makeDir(std::string filename)
{
    //TODO: FIX MEMORY LEAKS!
	BaseFileType* newDir = new BaseFileType(ppc::FileType::Directory);
    newDir->name = filename;
	newDir->contents["."] = newDir;
	newDir->contents[".."] = this;
	this->contents[filename] = newDir;
	return newDir;
}

ppc::BaseFileType * ppc::BaseFileType::findElement(std::string filename)
{
    std::string lowerCaseFilename = filename;
    for (unsigned int i = 0; i < lowerCaseFilename.size(); i++) {
        lowerCaseFilename[i] = tolower(lowerCaseFilename[i]);
    }
	for (auto iter = this->contents.begin(); iter != this->contents.end(); iter++) {
        std::string lowerCaseIter = iter->first;
        for (unsigned int i = 0; i < lowerCaseIter.size(); i++) {
            lowerCaseIter[i] = tolower(lowerCaseIter[i]);
        }
		if (lowerCaseIter == lowerCaseFilename) {
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
	passwordVector_.push_back(pwd);
	passwordProtected = true;
	passwordHint = hint;
}

void ppc::BaseFileType::addPassword(std::string pwd) {
	passwordVector_.push_back(pwd);
}

bool ppc::BaseFileType::comparePassword(std::string input)
{
    for (unsigned int i = 0; i < input.size(); i++) {
        input[i] = tolower(input[i]);
    }
    //for (unsigned int i = 0; i < password.size(); i++) {
       // password[i] = tolower(password[i]);
    //}

	for (auto iter = passwordVector_.begin(); iter != passwordVector_.end(); iter++) {
		std::string tempIter = (*iter);
		for (int i = 0; i < tempIter.size(); i++) {
			tempIter[i] = tolower(tempIter[i]);
		}
		if (tempIter == input) {
			passwordProtected = false;
			return true;
		}
	}

    //if (input == password) {
		//passwordProtected = false;
		//return true;
	//}
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

void ppc::BaseFileType::setSuspicionLevel(unsigned int val)
{
	suspicionLevel = val;
}

int ppc::BaseFileType::getSuspicionLevel()
{
	return suspicionLevel;
}

std::string ppc::BaseFileType::getName()
{
	return this->name;
}


