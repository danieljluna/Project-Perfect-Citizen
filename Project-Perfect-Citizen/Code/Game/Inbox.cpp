#include "Inbox.h"

using namespace ppc;

Inbox::Inbox() {}

bool Inbox::isEmpty() { return messageList.empty(); }

Email* Inbox::getEmailAt(int pos) { return messageList.at(pos); }

int Inbox::getInboxSize() { return messageList.size(); }

void Inbox::addEmailToList(Email* newEmail) { messageList.push_back(newEmail); }

void Inbox::removeEmailFromList(int position) { 
	messageList.erase(messageList.begin()+position); 
}

int Inbox::getMaxSize(){
    return maxSize;
}

ppc::Subject& ppc::Inbox::getInboxSubject()
{
	return inboxSubject_;
}
