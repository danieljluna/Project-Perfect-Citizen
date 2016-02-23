// debug.cpp
// Nader Sleem

#include "debug.h"

using namespace ppc;


Debug::flagset Debug::flags;

void Debug::scanOpts(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "No flags entered in cmd line" << std::endl;
		return;
	}

	for (int i = 1; i < argc; i++) {

        std::string flags = argv[i];

		size_t found = flags.find('@');
		if (found == std::string::npos) {
			continue;
		}
		//substr should have found the flags
		// starting from the @

		flags = flags.substr(found);
		setFlags(flags);
	}
}

void Debug::setFlags(std::string& flag) {
	//flag will always start with '@'
	
	//If the only flag found was @, then
	//all flags must be turned on.
	if (flag.length() == 1) {
		flags.set();
		return;
	}

	size_t M = flag.find_first_not_of('@');
	size_t m = M + 1;
	if (m >= flag.length()) {
        std::cerr << "Invalid flag: " << flag << std::endl;
		return;
	}
	for (; m <= flag.length(); M+=2, m+=2) {
		unsigned char major = flag.at(M);
		unsigned char minor = flag.at(m);

		//Get the alphabetical positions of
		// the flags, based on their ASCII code
		int alphaPosMajor = (major - 'a') + 1;
		int alphaPosMinor = (minor - 'a') + 1;

		size_t majorRangeMin = (alphaPosMajor - 1) * MINOR_FLAGS;
		size_t majorRangeMax = (alphaPosMajor * MINOR_FLAGS) - 1;

		if (minor == '_') {
			for (size_t i = majorRangeMin; i <= majorRangeMax; i++) {
				flags.set(i);
			}
			continue;
		} else {
			flags.set(majorRangeMin + ((alphaPosMinor - 1) % MINOR_FLAGS));
		}
	}
}

//DO NOT USE '_' IN THE FLAG. '_' is a special flag signifier,
// not an actual flag.
bool Debug::getFlag(std::string flag) {
	if (flag.length() != 2) {
        std::cerr << "Invalid Flag: " + flag << std::endl;
		return false;
	}
	unsigned char major = flag.front();
	unsigned char minor = flag.back();

	if (minor == '_') {
        std::cerr << "Invalid Flag: " + flag << std::endl;
		return false;
	}
	int alphaPosMajor = (major - 'a') + 1;
	int alphaPosMinor = (minor - 'a') + 1;

	size_t majorRangeMin = (alphaPosMajor - 1) * MINOR_FLAGS;

	return flags.test(majorRangeMin + 
		((alphaPosMinor-1) % MINOR_FLAGS));

}

void Debug::where(std::string flag, const char* file, int line,
	const char* func) {
    std::string f = file;
    std::string fileName;
	fileName = f.substr(f.find_last_of("/\\")+1);
    std::cout << "DEBUG(" << flag << ") " <<
		fileName << " [Line:" << line << "] " << 
		func << "()" << std::endl;
}
