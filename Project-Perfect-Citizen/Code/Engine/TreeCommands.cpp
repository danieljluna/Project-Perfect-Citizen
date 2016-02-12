#include "TreeCommands.h"

fnMap functionMap{
	{ "cd"    , fn_cd },
	{ "ls"    , fn_ls },
	{ "make"  , fn_mkfile },
	{ "mkdir" , fn_mkDir }
};

commandFn findFunction(const std::string& command) {
	auto result = functionMap.find(command);
	if (result == functionMap.end()) {
		cout << "function not found" << endl;
	//	throw std::exception("TreeCommands::findFunction() :function not found");
	}
	return result->second;
}

void fn_mkfile(ppc::NodeState& state, const vector<string> words)
{
	string filename = words.at(1);
	string content = "";
	if (words.size() >= 3) {
		content = words.at(2);
	}
	state.getCwd()->makeFile(filename, content);
}

void fn_ls(ppc::NodeState& state, const vector<string> words)
{
	if (words.size() == 1) {
		state.getCwd()->printDir();
		return;
	}
	if (words.size() > 1) {
		if (words.at(1) == "/") {
			state.getRoot()->printDir();
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
		if (tempCwd->getFileType() == ppc::FileType::File) {
			return;
		}
	}
	state.printWorking();
	//state.printWorking();
	tempCwd->printDir();
}

void fn_cd(ppc::NodeState& state, const vector<string> words)
{
	if (words.size() == 1) {
		return;
	}
	if (words.at(1) == ".") {
		return;
	}
	if (words.at(1) == "/" || words.at(1).substr(0,1) == "/") {
		state.moveToRoot();
	}
	if (words.at(1) == "..") {
		state.setCwd((state.getCwd()->getParent()));
		state.popWorking();
	}
	std::string filePath = words.at(1);
	std::vector<std::string> pathVec = split(filePath, "/");
	ppc::BaseFileType* newDir = state.getCwd();
	ppc::BaseFileType* parent = state.getCwd()->getParent();
	for (auto iter = pathVec.begin(); iter != pathVec.end(); iter++) {
		newDir = newDir->findElement(*iter);
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
			state.pushWorking(*iter);
		}
	}
	state.setCwd(newDir);
}

void fn_mkDir(ppc::NodeState& state, const vector<string> words)
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
	}
}

std::vector<string> split(std::string line, std::string delimiter)
{
	size_t end = 0;
	std::vector<string> results;
	std::string token;
	for (;;) {
		size_t start = line.find_first_not_of(delimiter, end);
		if (start == string::npos) break;
		end = line.find_first_of(delimiter, start);
		results.push_back(line.substr(start, end - start));
	}
	return results;
}

void printVector(std::vector<std::string> vec)
{
	cout << "Printing vector" << endl;
	for (auto iter = vec.begin(); iter != vec.end(); iter++) {
		std::cout << *iter << std::endl;
	}
}
