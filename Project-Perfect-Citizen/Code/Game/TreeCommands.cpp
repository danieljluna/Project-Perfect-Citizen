#include "../Engine/debug.h"
#include "TreeCommands.h"
#include "../Engine/NodeState.h"
#include <string>

using namespace ppc;

fnMap functionMap{
	{ "cd"		,	fn_cd		},
	{ "ls"		,	fn_ls		},
	{ "make"	,	fn_mkfile	},
	{ "mkdir"	,	fn_mkDir	},
	{ "decrypt"	,	fn_decrypt	},
	{ "encrypt"	,   fn_decrypt	},
	{ "pwd"     ,   fn_pwd		},
	{ "unlock"	,	fn_unlock	},
	{ "flag"	,	fn_flag		}
};

commandFn ppc::findFunction(const std::string& command) {
	auto result = functionMap.find(command);
	if (result == functionMap.end()) {
        std::cout << "function not found" << std::endl;
		throw std::runtime_error("TreeCommands::findFunction() :function not found");
	}
	return result->second;
}

void ppc::fn_mkfile(ppc::NodeState& state, const std::vector<std::string> words)
{
    std::string filename = words.at(1);
    std::string content = "";
	if (words.size() >= 3) {
		content = words.at(2);
	}
	state.getCwd()->makeFile(filename, content);
	state.getCwd()->findElement(filename)->setName(filename);
}

void ppc::fn_ls(ppc::NodeState& state, const std::vector<std::string> words)
{
	if (words.size() == 1) {
		state.printWorking();
		state.getCwd()->printDir();
		state.setLastLsNode(state.getCwd());
		return;
	}
	if (words.size() > 1) {
		if (words.at(1) == "/") {
			state.getRoot()->printDir();
			state.setLastLsNode(state.getRoot());
			return;
		}
	}
	ppc::BaseFileType* tempCwd;
	std::string pathName = words.at(1);
	if (pathName.substr(0, 1) == "/") {
		tempCwd = state.getRoot();
	}
	else {
		tempCwd = state.getCwd();
	}
	std::vector<std::string> pathVec = split(pathName, "/");
	for (auto itor = pathVec.begin(); itor != pathVec.end(); itor++) {

		tempCwd = tempCwd->findElement(*itor);
		if (tempCwd == nullptr) {
			return;
		}
		if (tempCwd->getFileType() == FileType::File) {
			return;
		}
	}
	if (tempCwd->isEncrypted()) {
		std::cout << "Access Denied: Directory Encrypted" << std::endl;
		return;
	}
	if (tempCwd->isHidden()) {
		return;
	}
	state.printWorking();
	tempCwd->printDir();
	state.setLastLsNode(tempCwd);
}

void ppc::fn_cd(ppc::NodeState& state, const std::vector<std::string> words)
{
	if (words.size() == 1) {
		return;
	}
	if (words.at(1) == ".") {
		return;
	}
	if (/*words.at(1) == "/" ||*/ words.at(1).substr(0,1) == "/") {
		state.moveToRoot();
		if (words.at(1).size() == 1) {
			return;
		}
	}
	if (words.at(1) == "..") {
		if (state.getCwd() == state.getRoot()) {
			return;
		}
		state.setCwd((state.getCwd()->getParent()));
		state.popWorking();
		return;
	}
	std::string filePath = words.at(1);
	std::vector<std::string> pathVec = split(filePath, "/");
	ppc::BaseFileType* newDir = state.getCwd();
	ppc::BaseFileType* parent = state.getCwd()->getParent();
	for (auto iter = pathVec.begin(); iter != pathVec.end(); iter++) {
		newDir = newDir->findElement(*iter);
		if (newDir->isPasswordProtected()) {
			std::cout << "Access Denied: Directory is Password Protected" << std::endl;
			return;
		}

		if (newDir->isEncrypted()) {
			std::cout << "Access Denied: Directory is Encrypted" << std::endl;
			return;
		}

		if (newDir == nullptr) {
			return;
		}
		if (newDir->getFileType() == ppc::File) {
			return;
		}
		if (newDir == parent && newDir != state.getRoot()) {
			state.popWorking();
		}
		else {
			if (*iter != "..") {
				state.pushWorking(*iter);
			}
			if (*iter == "..") {
				state.popWorking();
			}
		}
	}
	state.setCwd(newDir);
}

void ppc::fn_mkDir(ppc::NodeState& state, const std::vector<std::string> words)
{
	if (words.size() == 1) {
		return;
	}
	ppc::BaseFileType* tempCWD;
	if (words.at(1).substr(0, 1) == "/") {
		tempCWD = state.getRoot();
	}
	else {
		tempCWD = state.getCwd();
	}
	std::string filePath = words.at(1);
	std::vector<std::string>vecPath = split(filePath, "/");

	for (auto itor = vecPath.begin(); itor != vecPath.end(); itor++) {
		tempCWD =  tempCWD->makeDir(*itor);
		if (tempCWD == nullptr) {
			return;
		}
	}
}

void ppc::fn_decrypt(ppc::NodeState& state, const std::vector<std::string> words)
{
	if (words.size() == 1) {
		return;
	}
	ppc::BaseFileType* tempCWD;
	if (words.at(1).substr(0, 1) == "/") {
		tempCWD = state.getRoot();
	}
	else {
		tempCWD = state.getCwd();
	}
    std::string filepath = words.at(1);
	std::vector<std::string> pathVec = split(filepath, "/");
	int i = 0;
	for (auto iter = pathVec.begin(); iter != pathVec.end(); iter++) {
		tempCWD = tempCWD->findElement(pathVec.at(i));
	}
	if (words.at(0) == "decrypt") {
		tempCWD->setEncryption(false);
	}
	else {
		tempCWD->setEncryption(true);
	}
	
}

void ppc::fn_pwd(ppc::NodeState& state, const std::vector<std::string> words) {
    state.printWorking();
}

void ppc::fn_unlock(ppc::NodeState& state, const std::vector<std::string> words)
{
	printVector(words);

	if (words.size() == 1 || words.size() == 2) {
		std::cout << "invalid paramaters. Must be 'unlock [filename] [password] " << std::endl;
		return;
	}
	if (words.at(1).substr(0, 1) == "/") {
		std::cout << "You must be in the directory of the file or folder to unlock it"
			<< std::endl;
		return;
	}
	if (words.at(1).find_first_of("/") != std::string::npos) {
		std::cout << "Filepaths not allowed" << std::endl;
		return;
	}
	std::string filename = words.at(1);
	ppc::BaseFileType* tempCWD;
	tempCWD = state.getCwd()->findElement(filename);
	if (tempCWD == nullptr) {
		std::cout << "File not found" << std::endl;
		return;
	}
	if (!tempCWD->isPasswordProtected()) {
		std::cout << "File is not password protected" << std::endl;
		return;
	}
	bool isUnlocked = tempCWD->comparePassword(words.at(2));
	if (isUnlocked) {
		std::cout << "Access Granted" << std::endl;
		return;
	}
	std::cout << "Password Incorrect. Access Denied" << std::endl;
}

void ppc::fn_flag(ppc::NodeState& state, const std::vector<std::string> words) {

}


std::vector<std::string> ppc::split(std::string line, std::string delimiter)
{
	size_t end = 0;
	std::vector<std::string> results;
	std::string token;
	for (;;) {
		size_t start = line.find_first_not_of(delimiter, end);
		if (start == std::string::npos) break;
		end = line.find_first_of(delimiter, start);
		results.push_back(line.substr(start, end - start));
	}
	return results;
}

void ppc::printVector(std::vector<std::string> vec)
{
	for (auto iter = vec.begin(); iter != vec.end(); iter++) {
		std::cout << *iter << std::endl;
	}
}
