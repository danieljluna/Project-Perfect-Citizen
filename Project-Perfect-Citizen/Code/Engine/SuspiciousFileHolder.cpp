#include "SuspiciousFileHolder.h"

std::vector<ppc::BaseFileType*> ppc::SuspiciousFileHolder::bftVector_;
ppc::WindowInterface* ppc::SuspiciousFileHolder::susWindow_;
int ppc::SuspiciousFileHolder::staticCount_ = 0;
ppc::WindowInterface* susWindow_ = nullptr;
int ppc::SuspiciousFileHolder::badThreshold_ = 0;
int ppc::SuspiciousFileHolder::goodThreshold_ = 0;
bool ppc::SuspiciousFileHolder::guilty_ = false;
int ppc::SuspiciousFileHolder::susScore_ = 0;
ppc::Subject ppc::SuspiciousFileHolder::onChange;
//std::vector < ppc::SuspiciousFileHolder*> ppc::SuspiciousFileHolder::susVec_;



std::vector<ppc::BaseFileType*>& ppc::SuspiciousFileHolder::getBftVector()
{
	return bftVector_;
}

void ppc::SuspiciousFileHolder::flagFile(ppc::BaseFileType * file)
{
	if (bftVector_.size() < 3) {
		bftVector_.push_back(file);

        Event ev;
        ev.type = ev.SubmissionType;
        ev.submission.file = file;
        ev.submission.type = ev.submission.Mark;
        onChange.sendEvent(ev);
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
	//if (susWindow_ != nullptr) {
	//	susWindow_->close();
	//}
	susWindow_ = sWindow;
}

ppc::WindowInterface * ppc::SuspiciousFileHolder::getWindow()
{
	return susWindow_;
}


int ppc::SuspiciousFileHolder::getStaticCount()
{
	return staticCount_;
}


ppc::BaseFileType * ppc::SuspiciousFileHolder::getBFTVectorElement(int element)
{
	if (element >= bftVector_.size() || bftVector_.size() == 0) {
		return nullptr;
	}
	return bftVector_.at(element);
}

void ppc::SuspiciousFileHolder::submitFiles()
{
    Event ev;
    ev.type = ev.SubmissionType;
    ev.submission.count = bftVector_.size();
    ev.submission.type = ev.submission.Submit;
    onChange.sendEvent(ev);


	if (bftVector_.size() != 3) {
		//std::cout << "Need more files dingus" << std::endl;
		return;
	}


	int totalSuspicion = 0;
	for (auto iter = bftVector_.begin(); iter != bftVector_.end(); iter++) {
		totalSuspicion += (**iter).getSuspicionLevel();
	}


	if (totalSuspicion < goodThreshold_) {
		guilty_ = false;
		return;
	}
	else if (totalSuspicion > badThreshold_) {
		guilty_ = true;
	}
}

void ppc::SuspiciousFileHolder::clearFiles()
{
    Event ev;
    ev.type = ev.SubmissionType;
    ev.submission.type = ev.submission.Unmark;
    
    for (size_t i = 0; i < bftVector_.size(); ++i) {
        ev.submission.file = bftVector_.at(i);
        onChange.sendEvent(ev);
    }

	bftVector_.clear();
}

void ppc::SuspiciousFileHolder::clearFile(std::string doomedFile)
{
	for (auto iter = bftVector_.begin(); iter != bftVector_.end(); iter++) {
		if (doomedFile == (**iter).getName()) {
            Event ev;
            ev.type = ev.SubmissionType;
            ev.submission.file = *iter;
            ev.submission.type = ev.submission.Unmark;
            onChange.sendEvent(ev);

            bftVector_.erase(iter);

			return;
		}
	}
}

void ppc::SuspiciousFileHolder::setSusScore(int score)
{
	susScore_ = score;
}

bool ppc::SuspiciousFileHolder::isGuilty()
{
	return guilty_;
}
