#include "Email.h"


using namespace ppc;

Email::Email(std::string to, std::string from, std::string subject,
	std::string content, std::string attachment) {
	this->to = to;
	this->from = from;
	this->subject = subject;
	this->content = content;
	this->attachment = attachment;
	this->read = false;
}

std::string Email::getToField() { return this->to; }

std::string Email::getFromField() { return this->from; }

std::string Email::getSubjectField() { return this->subject; }

std::string Email::getContentField() { return this->content; }

std::string Email::getAttachmentField() { return this->attachment; }

void Email::setRead() { this->read = true; }
