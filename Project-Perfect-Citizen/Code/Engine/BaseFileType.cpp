#include "BaseFileType.h"

ppc::BaseFileType::BaseFileType()
{
	//switch (filetype) {
	//case FileType::Directory:
		//
	//}
}

void ppc::BaseFileType::readFile()
{
}

void ppc::BaseFileType::printDir()
{
	for (auto iter = this->contents.begin(); iter != this->contents.end(); iter++) {
		cout << iter->first << endl;
	}
}
