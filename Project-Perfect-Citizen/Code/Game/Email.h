#pragma once
#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////
/// @author Alex Vincent
/// @brief Object which holds the strings composing an email message
/// @details Contains four strings (to, from, contents, attachment),
/// that will usually exist in a vector in the inbox class.
/// @note member functions are basic getters/setter and shouldn't 
/// need any extensive comments. Member fields are also very straight-
/// forward and shouldn't need comments either. 
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class Email {

	public:

		///////////////////////////////////////////////////////////////////////
		///@brief Default constructor
		///@param The "To:" field string
		///@param The "From:" field string
		///@param The "Subject:" field string
		///@param The text contents of the email
		///@param The file name (with extension) represented as a string
		///////////////////////////////////////////////////////////////////////
		Email(std::string to, std::string from, std::string subject, 
              std::string content, bool visible, std::string attachment);

	///////////////////////////////////////////////////////////////////
	// ACCESSORS (Simple getters)
	///////////////////////////////////////////////////////////////////
		std::string getToField();
		std::string getFromField();
		std::string getSubjectField();
		std::string getAbbrevSubjectField();
		std::string getContentField();
		std::string getAttachmentField();
		bool getReadFlag();

	///////////////////////////////////////////////////////////////////
	// MUTATORS
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	///@brief Flips the read flag to the opposite of what it was
	///////////////////////////////////////////////////////////////////////
		void setRead();
        
        bool getVisible();
        
        void setVisible(bool b);

	protected:
		std::string to;
		std::string from;
		std::string subject;
		std::string content;
		std::string attachment;
		bool read = false;
        bool visible;

		///////////////////////////////////////////////////////////////////////
		///@brief The size of an abbreviated email subject line.
		///////////////////////////////////////////////////////////////////////
		int abbrevLimit = 30;
	};

}