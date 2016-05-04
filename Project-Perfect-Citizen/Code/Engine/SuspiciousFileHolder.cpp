#include "SuspiciousFileHolder.h"

std::vector<ppc::BaseFileType*> ppc::SuspiciousFileHolder::bftVector_;
ppc::WindowInterface* ppc::SuspiciousFileHolder::susWindow_;
int ppc::SuspiciousFileHolder::staticCount_ = 0;
ppc::WindowInterface* susWindow_ = nullptr;
//std::vector < ppc::SuspiciousFileHolder*> ppc::SuspiciousFileHolder::susVec_;



std::vector<ppc::BaseFileType*>& ppc::SuspiciousFileHolder::getBftVector()
{
	return bftVector_;
}

void ppc::SuspiciousFileHolder::flagFile(ppc::BaseFileType * file)
{
	if (bftVector_.size() < 3) {
		bftVector_.push_back(file);
	}
}

unsigned int ppc::SuspiciousFileHolder::getFileSuspicion(int element)
{
	return bftVector_.at(element)->getSuspicionLevel();
}

unsigned int ppc::SuspiciousFileHolder::getTotalSucpicion()
{
	if (bftVector_.empty()) {
		return 0;
	}
	unsigned int susLevel = 0;
	for (auto iter = bftVector_.begin(); iter != bftVector_.end(); iter++) {
		susLevel += (*iter)->getSuspicionLevel();
	}
	return susLevel;
}

void ppc::SuspiciousFileHolder::printSuspiciousVector()
{
	for (auto iter = bftVector_.begin(); iter != bftVector_.end(); iter++) {
		std::cout << "File name: " << (*iter)->getName() << " Suspicion Level: " << std::to_string((**iter).getSuspicionLevel()) << std::endl;
	}
}

void ppc::SuspiciousFileHolder::setWindow(ppc::WindowInterface * sWindow)
{
	if (susWindow_ != nullptr) {
		susWindow_->close();
	}
	susWindow_ = sWindow;
}

ppc::WindowInterface * ppc::SuspiciousFileHolder::getWindow()
{
	return susWindow_;
}

//ppc::SuspiciousFileHolder* ppc::SuspiciousFileHolder::getSusVecElement(int element)
//{
	//if (element >= susVec_.size() || susVec_.size() == 0) {
		//return nullptr;
	//}
	//return susVec_.at(element);
//}

int ppc::SuspiciousFileHolder::getStaticCount()
{
	return staticCount_;
}

//int ppc::SuspiciousFileHolder::pushWindow(ppc::SuspiciousFileHolder * fileHolder)
//{
	//susVec_.push_back(fileHolder);
	//staticCount_++;
	//return (staticCount_ - 1);
//}

ppc::BaseFileType * ppc::SuspiciousFileHolder::getBFTVectorElement(int element)
{
	if (element >= bftVector_.size() || bftVector_.size() == 0) {
		return nullptr;
	}
	return bftVector_.at(element);
}
