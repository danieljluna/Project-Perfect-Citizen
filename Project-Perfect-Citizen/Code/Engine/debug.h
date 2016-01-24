// debug.h
// Nader Sleem

#pragma once

#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

// Each Flag is ALWAYS a string with two chars
// -@[Major]_... - Turn on all minor flags of the major
// -@[Major][Minor]... - Turn on the specifc Minor flag of the Major
// Major should refer to a specific class/file
// Because of implementation to mimimize the space flags take 
// up in memory, there can be flag "collisions" in the bits 
// pertaining to the flag.
// For example - -@da & -@di map to the same bit. 
// Will probably have to fix the implementation in order to avoid 
// this, but since we don't know what flags we are going to have 
// for each files (and unknown future files) it is hard to forsee
// how many combinations of flags we will have.
// 
// Note: Tell people they cannot make up their own flags w/o running it past me
class Debug {

private:
	static const int FLAG_COUNT = 26;
	static const int MINOR_FLAGS = 8;
	// 26 (# of letters)  *   8 (Minor flags) = 208 bits = 26 bytes
	using flagset = bitset<FLAG_COUNT * MINOR_FLAGS>; 
	
	static flagset flags;

	//make Ctor private?
	Debug();

	static void setFlags(string& flag);

public:
	static void scanOpts(int argc, char** argv);
	static bool getFlag(string flag);

	static void where(string flag, const char* file, int line, 
		const char* func);

#ifdef NDEBUG
#define DEBUGF(FLAG,CODE) ;
#define DEBUGS(FLAG,STMT) ;
#else
#define DEBUGF(FLAG,CODE) { \
           if (Debug::getFlag (FLAG)) { \
              Debug::where (FLAG, __FILE__, __LINE__, __func__); \
              cerr << CODE << endl; \
           } \
        }
#define DEBUGS(FLAG,STMT) { \
           if (Debug::getFlag (FLAG)) { \
              Debug::where (FLAG, __FILE__, __LINE__, __func__); \
              STMT; \
           } \
        }
#endif

};
