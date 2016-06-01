#include "SuspiciousFileHolder.h"
#include "../Engine/World.h"
#include "../Game/createWindow.h"
#include "../Engine/Window.h"
#include "../Engine/World.h"
#include "../Engine/desktop.h"

std::vector<ppc::BaseFileType*> ppc::SuspiciousFileHolder::bftVector_;
ppc::WindowInterface* ppc::SuspiciousFileHolder::susWindow_;
int ppc::SuspiciousFileHolder::staticCount_ = 0;
ppc::WindowInterface* susWindow_ = nullptr;
int ppc::SuspiciousFileHolder::badThreshold_ = 20;
int ppc::SuspiciousFileHolder::goodThreshold_ = 20;
bool ppc::SuspiciousFileHolder::guilty_ = false;
int ppc::SuspiciousFileHolder::susScore_ = 0;
ppc::Subject ppc::SuspiciousFileHolder::onChange;
//std::vector < ppc::SuspiciousFileHolder*> ppc::SuspiciousFileHolder::susVec_;

int ppc::SuspiciousFileHolder::finalScore_ = 0;

std::vector<ppc::BaseFileType*>& ppc::SuspiciousFileHolder::getBftVector()
{
	return bftVector_;
}

void ppc::SuspiciousFileHolder::flagFile(ppc::BaseFileType * file)
{
	WindowInterface* flagResponse = new ppc::Window(300, 150, sf::Color(170, 170, 170));
	if (isInFileHolder(file)) {
	
		spawnErrorMessage(flagResponse, flagResponse->getInputHandler(),
			World::getCurrDesktop().getButtonSheet(), 300, 250,
			"Error: File '" + file->getName() + "' has already been flagged.", "Existing File Flagged");
		World::getCurrDesktop().addWindow(flagResponse);
		return;
	}

	if (bftVector_.size() < 3) {
		bftVector_.push_back(file);

		Event ev;
		ev.type = ev.SubmissionType;
		ev.submission.file = file;
		ev.submission.type = ev.submission.Mark;
		onChange.sendEvent(ev);
	}
	else {
		spawnErrorMessage(flagResponse, flagResponse->getInputHandler(), World::getCurrDesktop().getButtonSheet(),
			200, 200, "Error: You may only flag 3 files.", "File Holder is full");
		World::getCurrDesktop().addWindow(flagResponse);
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
		susWindow_ = sWindow;
	}
	else susWindow_ = sWindow;
	
}

ppc::WindowInterface * ppc::SuspiciousFileHolder::getWindow()
{
	return susWindow_;
}


int ppc::SuspiciousFileHolder::getStaticCount()
{
	return staticCount_;
}

bool ppc::SuspiciousFileHolder::isInFileHolder(ppc::BaseFileType* file) {

	for (unsigned int i = 0; i < bftVector_.size(); ++i) {
		if (file == bftVector_.at(i)) return true;
	}
	return false;
}


ppc::BaseFileType * ppc::SuspiciousFileHolder::getBFTVectorElement(unsigned int element)
{
	if (element >= bftVector_.size() || bftVector_.size() == 0) {
		return nullptr;
	}
	return bftVector_.at(element);
}

void ppc::SuspiciousFileHolder::submitFiles()
{
	if (bftVector_.size() != 3) {
		return;
	}


	int totalSuspicion = 0;
	for (auto iter = bftVector_.begin(); iter != bftVector_.end(); iter++) {
		totalSuspicion += (**iter).getSuspicionLevel();
	}

	finalScore_ = totalSuspicion;

	if (totalSuspicion < goodThreshold_) {
		guilty_ = false;
	}
	else if (totalSuspicion > badThreshold_) {
		guilty_ = true;
	}

	if (totalSuspicion >= 30) {
		World::setCurrReportType(World::ReportType::A);
	} else if (totalSuspicion >= 20 && totalSuspicion <= 29) {
		World::setCurrReportType(World::ReportType::B);
	} else if (totalSuspicion >= 10 && totalSuspicion <= 19) {
		World::setCurrReportType(World::ReportType::C);
	} else if (totalSuspicion >= 1 && totalSuspicion <= 9) {
		World::setCurrReportType(World::ReportType::D);
	}

	Event ev;
	ev.type = ev.SubmissionType;
	ev.submission.count = bftVector_.size();
	ev.submission.type = ev.submission.Submit;
	onChange.sendEvent(ev);

	clearFiles();
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

int ppc::SuspiciousFileHolder::getFinalScore() 
{
	return finalScore_;
}
