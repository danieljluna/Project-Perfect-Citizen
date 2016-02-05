#pragma once
#include "BaseFileType.h"
namespace ppc {
	enum FileType {Test,TestTwo,TestThree};

	class TreeNode {
		friend class NodeState;
	private:
		BaseFileType contents;
	public:
		TreeNode(FileType filetype);
	};
}