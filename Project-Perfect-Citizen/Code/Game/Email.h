#pragma once
#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////
/// @author Alex Vincent
/// @brief Object which holds the strings composing and email message
/// @details Contains four strings (to, from, contents, attachement),
/// that will usually exist in a vector in the inbox class
///////////////////////////////////////////////////////////////////////

namespace ppc {

	// friend class is Inbox

	class Email {

	public:

		///////////////////////////////////////////////////////////////////////
		///@brief Default constructor
		///////////////////////////////////////////////////////////////////////
		Email(std::string to, std::string from, std::string subject, 
			std::string content, std::string attachment);

	///////////////////////////////////////////////////////////////////
	// ACCESSORS
	///////////////////////////////////////////////////////////////////
		std::string getToField();
		std::string getFromField();
		std::string getSubjectField();
		std::string getContentField();
		std::string getAttachmentField();

	///////////////////////////////////////////////////////////////////
	// MUTATORS
	///////////////////////////////////////////////////////////////////
		void setRead();

	protected:
		std::string to;
		std::string from;
		std::string subject;
		std::string content;
		std::string attachment;
		bool read;
	};

}