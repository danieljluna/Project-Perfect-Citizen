#include "SuspiciousFileHolder.h"

std::vector<ppc::BaseFileType*> SuspiciousFileHolder::bftVector_;

std::vector<ppc::BaseFileType*>& SuspiciousFileHolder::getBfgVector()
{
	return bftVector_;
}

void SuspiciousFileHolder::flagFile(ppc::BaseFileType * file)
{
	if (bftVector_.size() < 3) {
		bftVector_.push_back(file);
	}
}

unsigned int SuspiciousFileHolder::getFileSuspicion(int element)
{
	return bftVector_.at(element)->getSuspicionLevel();
}

unsigned int SuspiciousFileHolder::getTotalSucpicion()
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
