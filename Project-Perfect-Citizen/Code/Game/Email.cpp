#include "Email.h"
#include <algorithm>

using namespace ppc;

Email::Email(std::string to, std::string from, std::string subject,
	std::string content, bool visible, std::string attachment) {
	this->to = to;
	this->from = from;
	this->subject = subject;
	this->content = content;
	this->attachment = attachment;
	this->read = false;
    this->visible = visible;
}

std::string Email::getToField() { return this->to; }

std::string Email::getFromField() { return this->from; }

std::string Email::getSubjectField() { return this->subject; }

std::string Email::getAbbrevSubjectField() {
	std::string abbrev = this->subject;
	for (size_t i = 0; i < subject.size(); ++i) {
		abbrev.erase(std::remove(abbrev.begin(), abbrev.end(), '\n'), abbrev.end());
	}

	if (abbrev.size() > abbrevLimit) return abbrev.substr(0, abbrevLimit) + "...";
	else return abbrev;
}

std::string Email::getContentField() { return this->content; }

std::string Email::getAttachmentField() { return this->attachment; }

bool Email::getReadFlag() { return this->read;  }

void Email::setRead() { this->read = true; }

bool Email::getVisible() { return this->visible; }

void Email::setVisible(bool b) { this->visible = b; }
