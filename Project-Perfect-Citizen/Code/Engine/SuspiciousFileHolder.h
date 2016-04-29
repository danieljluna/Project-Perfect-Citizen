#pragma once
#include "BaseFileType.h"
#include <iostream>
#include <string>
#include <vector>

namespace ppc {
	class SuspiciousFileHolder {
	private:
		const unsigned int MAX_SIZE_ = 3;
		static std::vector<ppc::BaseFileType*> bftVector_;
	public:
		SuspiciousFileHolder();
		~SuspiciousFileHolder();
		static std::vector<ppc::BaseFileType*>& getBfgVector();
		static void flagFile(ppc::BaseFileType* file);
		static unsigned int getFileSuspicion(int element);
		static unsigned int getTotalSucpicion();

	};
};
