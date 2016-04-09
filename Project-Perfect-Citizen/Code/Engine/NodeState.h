#pragma once
#include <vector>

///////////////////////////////////////////////
///Class node state is a class used to monitor
///a single tree. It contains links to the 
///root of the tree along with the current
///mode of the tree (CWD). The nodeState
///class also holds a vector used to keep
///track of the CWD as well. This vector
///is updated when CDing around the tree
///////////////////////////////////////////////
namespace ppc {
    class BaseFileType;

	class NodeState {
		friend class BaseFileType;
	private:
		///////////////////////////////////////////////
		///@brief pointer to root of file tree
		///////////////////////////////////////////////
		BaseFileType* root;
		///////////////////////////////////////////////
		///@brief pointer to cwd of file tree
		///////////////////////////////////////////////
		BaseFileType* cwd;
		///////////////////////////////////////////////
		///@brief vector of strings that keeps track of
		///the current working directory
        std::vector<std::string> workingDirectory;
		///////////////////////////////////////////////
		///@brief the last node to be "printed by ls"
		///used in pairing with dirString
		///////////////////////////////////////////////
		BaseFileType* lastLsNode;
		///////////////////////////////////////////////
		///@brief a string representation of every 
		///element in lastLsNode. Each element is seperated
		///by '@' and needs to be parsed. 
		///////////////////////////////////////////////
		std::string dirString = "";
	public:
		///////////////////////////////////////////////
		///@brief Default Ctor
		///////////////////////////////////////////////
		NodeState();

		///////////////////////////////////////////////
		///@brief Copy Ctor
		///////////////////////////////////////////////
		NodeState(const NodeState&);

		///////////////////////////////////////////////
		///@brief pops off the last element in the
		///workingDirectory vector. Primarily used 
		///when dealing with changing directories. 
		///////////////////////////////////////////////
		void popWorking();
		///////////////////////////////////////////////
		///@brief calls push_back() on workingDirectory
		///with string param
		///@param Filename is the name of the directory
		///Do not imput a filePath, only a directory
		///name
		///////////////////////////////////////////////
		void pushWorking(std::string filename);
		///////////////////////////////////////////////
		///@brief Prints the current working directory
		/// "/" is considered root. 
		///////////////////////////////////////////////
		void printWorking();
		///////////////////////////////////////////////
		///@brief sets up the root of the file tree
		///must be called as soon as Node state is
		///created
		///@Sets up the root directory. Sets CWD to root
		///sets root to itself; Adds . and .. to the root
		///directory
		///////////////////////////////////////////////
		void setUp();
		///////////////////////////////////////////////
		///@brief assigns a BaseFileType node to the CWD
		///@param NewCwd is the new BaseFileType to become
		///CWD. Eror if the BaseFileType is not of 
		///ppc::FileType::Directory
		///////////////////////////////////////////////
		void setCwd(BaseFileType* newCwd);
		///////////////////////////////////////////////
		///@brief returns the CWD;
		///////////////////////////////////////////////
		BaseFileType* getCwd();
		///////////////////////////////////////////////
		///@brief returns the root;
		///////////////////////////////////////////////
		BaseFileType* getRoot();
		///////////////////////////////////////////////
		///@brief sets the CWD to Root, resets the 
		///working directory to its starting state
		///containing only "/"
		///////////////////////////////////////////////
		void moveToRoot();
		///////////////////////////////////////////////
		///@brief returns the pwdVector;
		///////////////////////////////////////////////
		std::vector<std::string> getPwdVector();
		///////////////////////////////////////////////
		///@brief assigns a node* to this->lastLsNode
		///used in fn_ls to determine the directory
		///that will be printed.
		///@param node* to be assigned
		///////////////////////////////////////////////
		void setLastLsNode(BaseFileType* node);
		///////////////////////////////////////////////
		///@brief returns this->dirstring
		///@details The string contains every element in
		///this->lastLSNode's directory. Every element is
		///seperated by '@' and must be parsed out
		///////////////////////////////////////////////
        std::string getDirString();
	};
}; //end ppc namespace