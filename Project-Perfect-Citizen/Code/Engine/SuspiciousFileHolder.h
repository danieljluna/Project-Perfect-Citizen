#pragma once
#include "BaseFileType.h"
#include <iostream>
#include <string>
#include <vector>
#include"WindowInterface.h"


//for my sanity a suspicious file holder holds a vector of suspicious file holders that each hold 3 files tops. 
namespace ppc {
	static class SuspiciousFileHolder {
	private:
		SuspiciousFileHolder() = delete;
		~SuspiciousFileHolder() = delete;
		const unsigned int MAX_SIZE_ = 3;
		static std::vector<ppc::BaseFileType*> bftVector_;
		static ppc::WindowInterface* susWindow_;
		//static std::vector<ppc::SuspiciousFileHolder*> susVec_;
		static int staticCount_;
	public:
		static std::vector<ppc::BaseFileType*>& getBftVector();
		static void flagFile(ppc::BaseFileType* file);
		static unsigned int getFileSuspicion(int element);
		static unsigned int getTotalSucpicion();
		static void printSuspiciousVector();
		static void setWindow(ppc::WindowInterface* sWindow);
		static ppc::WindowInterface* getWindow();
		//static ppc::SuspiciousFileHolder* getSusVecElement(int element);
		static int getStaticCount();
		//static int pushWindow(ppc::SuspiciousFileHolder* fileHolder);
		static ppc::BaseFileType* getBFTVectorElement(int element);
	};
};
