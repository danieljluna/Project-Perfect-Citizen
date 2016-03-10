#include "debug.h"
#include "BaseFileType.h"

ppc::BaseFileType::BaseFileType(ppc::FileType type)
{
	switch (filetype) {
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

ppc::BaseFileType::~BaseFileType() {
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

void ppc::BaseFileType::uploadJson(std::string jString)
{
	this->jSonString = jString;
}

void ppc::BaseFileType::readFile()
{
	if (this->encrypted) {
		return;
	}
	switch (this->filetype) {
	case FileType::File:
		std::cout << this->data << std::endl;

	}
}

void ppc::BaseFileType::printDir()
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

void ppc::BaseFileType::makeFile(std::string filename, std::string content)
{
	BaseFileType* newFile = new BaseFileType(ppc::FileType::File);
	this->contents[filename] = newFile;
}

ppc::BaseFileType* ppc::BaseFileType::makeDir(std::string filename)
{
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

ppc::BaseFileType * ppc::BaseFileType::getParent()
{
	return this->findElement("..");
}

ppc::FileType ppc::BaseFileType::getFileType()
{
	return this->filetype;
}

void ppc::BaseFileType::setVisibility(bool flag)
{
	this->hidden = flag;
}

void ppc::BaseFileType::setEncryption(bool flag) {
	this->encrypted = flag;
}

bool ppc::BaseFileType::isHidden()
{
	return hidden;
}

bool ppc::BaseFileType::isEncrypted()
{
	return encrypted;
}

std::map<std::string, ppc::BaseFileType*> ppc::BaseFileType::getContents()
{
	return this->contents;
}


