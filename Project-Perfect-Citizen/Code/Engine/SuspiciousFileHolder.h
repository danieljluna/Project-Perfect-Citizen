#pragma once
#include "BaseFileType.h"
#include <iostream>
#include <string>
#include <vector>
#include"WindowInterface.h"

namespace ppc {
	class SuspiciousFileHolder {
	private:
		const unsigned int MAX_SIZE_ = 3;
		static std::vector<ppc::BaseFileType*> bftVector_;
		static ppc::WindowInterface* susWindow_;
	public:
		SuspiciousFileHolder();
		~SuspiciousFileHolder();
		static std::vector<ppc::BaseFileType*>& getBfgVector();
		static void flagFile(ppc::BaseFileType* file);
		static unsigned int getFileSuspicion(int element);
		static unsigned int getTotalSucpicion();
		static void printSuspiciousVector();
	};
};
