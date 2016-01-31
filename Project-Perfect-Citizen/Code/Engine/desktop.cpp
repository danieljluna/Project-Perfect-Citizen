//desktop.cpp
// Nader Sleem

#include "desktop.h"

ppc::Desktop::Desktop() {
	os_ = nullptr;
	ft_ = nullptr;
}

ppc::Desktop::Desktop(windVec windows, 
	operatingSys &os, fileTree &ft) {

	os_ = &os;
	ft_ = &ft;
	windows_ = windows;
}

ppc::Desktop::~Desktop() {
	if (os_ != nullptr) delete os_;
	if (ft_ != nullptr) delete ft_;
}

const operatingSys& ppc::Desktop::getOS() const {
	return *os_;
}

const fileTree& ppc::Desktop::getFileTree() const {
	return *ft_;
}

ppc::Desktop::windVec::iterator ppc::Desktop::getIter(window* w) {
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		if (*it == w) {
			return it;
		}
	}
	return windows_.end();
}

ppc::Desktop::windVec::iterator ppc::Desktop::windVecBegin() {
	return windows_.begin();
}

ppc::Desktop::windVec::iterator ppc::Desktop::windVecEnd() {
	return windows_.end();
}

ppc::Desktop::windVec::iterator ppc::Desktop::addWindow(window* w) {
	windows_.push_back(w);
	return windows_.end() - 1;
}

void ppc::Desktop::removeWindow(window* w) {
	auto it = ppc::Desktop::getIter(w);
	ppc::Desktop::removeWindow(it);
}

void ppc::Desktop::removeWindow(windVec::iterator it) {
	windows_.erase(it);
}