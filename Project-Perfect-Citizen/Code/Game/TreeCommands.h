#pragma once
#include "../Engine/NodeState.h"
#include "../Engine/BaseFileType.h"
#include <map>


namespace ppc {

using commandFn = void(*)(ppc::NodeState& state, const std::vector<std::string> words);
using fnMap = std::map<std::string, commandFn>;

///////////////////////////////////////////////
///@brief used in combination with the fnMap
///to find the correct command to call from the
///real life or in game console.
///////////////////////////////////////////////
commandFn findFunction(const std::string& command);
///////////////////////////////////////////////
///@brief creates a directory at the targeted
///filepath. If the path to the directory doesnt
///exist, then directories are created along
///the way.
///@param inode state for the tree in question
///@param words are the commands being passed
///from the console
///////////////////////////////////////////////
void fn_mkfile(ppc::NodeState& state, const std::vector<std::string> words);
///////////////////////////////////////////////
///@brief prints the directory at targeted
///filepath. Error if the path is anything 
///but a directory
///@param inode state for the tree in question
///@param words are the commands being passed
///from the console. words(1) is the filepath
///words(2) is the contents of the textfile
///////////////////////////////////////////////
void fn_ls(ppc::NodeState& state, const std::vector<std::string> words);
///////////////////////////////////////////////
///@brief Moves you to the targeted directory
///does nothing if the directory doesnt exist
///or if the target is not a directory
///@details also sets the last directory 
///that you used LS on to NodeState::LastLSNode
///Therefore you can call NodeState::getDirString()
///to get the string of what LS would normally print
///This string is seperated by @ characters and
///needs to be parsed. 
///@param inode state for the tree in question
///@param words are the commands being passed
///from the console
///////////////////////////////////////////////
void fn_cd(ppc::NodeState& state, const std::vector<std::string> words);
///////////////////////////////////////////////
///@brief 
///@param inode state for the tree in question
///@param words are the commands being passed
///from the console
///////////////////////////////////////////////
void fn_mkDir(ppc::NodeState& state, const std::vector<std::string> words);
///////////////////////////////////////////////
///@brief Helper function that splits a string
///by a delimiter. Returns a string vector
///@param line. String to be split up
///@param delimiter That the string is split up
///by
///////////////////////////////////////////////
std::vector<std::string> split(std::string line, std::string delimiter);

void fn_decrypt(ppc::NodeState& state, const std::vector<std::string>words);
void fn_pwd(ppc::NodeState& state, const std::vector<std::string> words);
void fn_unlock(ppc::NodeState& state, const std::vector<std::string> words);

//scan a file to reveal its hidden suspicion score. 
void fn_scan(ppc::NodeState& state, const std::vector<std::string> words);
void fn_flag(ppc::NodeState & state, const std::vector<std::string> words);

///////////////////////////////////////////////
///@brief helper function that prints a 
///string vector
///@param vec: string vector to be printed
///////////////////////////////////////////////
void printVector(std::vector<std::string> vec);


};