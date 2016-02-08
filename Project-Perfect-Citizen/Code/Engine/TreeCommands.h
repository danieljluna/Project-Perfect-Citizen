#pragma once
#include "NodeState.h"
#include "BaseFileType.h"

using commandFn = void(*)(ppc::NodeState& state, const vector<string> words);
using fnMap = std::map<string, commandFn>;

void fn_mkfile(ppc::NodeState& state, const vector<string> words);
void fn_ls(ppc::NodeState& state, const vector<string> words);
void fn_cd(ppc::NodeState& state, const vector<string> words);
void fn_mkDir(ppc::NodeState& state, const vector<string> words);

std::vector<string> split(std::string line, std::string delimiter);
void printVector(std::vector<std::string> vec);