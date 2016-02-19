// debug.h
// Nader Sleem & Daniel Luna

#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <bitset>
#include <string>
#include <vector>

namespace ppc {

    // Each Flag is ALWAYS a string with two chars
    // -@[Major]_ - Turn on all minor flags of the major
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

///////////////////////////////////////////////////////////////////////
///@brief Static class to maintain debug flags & print debug statements
///@details Command line flags must be the first argument in the 
///	command line. Flags must be formated as :
///		-@[Major][Minor]...[Major][Minor]
/// Where Major & Minor are single characters which together form a 
/// string of two chars. Flags must always be two chars long.
/// Every Major has the same amount of minor flags.
/// -@[Major][Minor] will turn on the specifc Minor flag of the Major
/// A flag of -@[Major]_ will turn on all the the Major's flags.
/// A flag of -@ turns on ALL flags.
/// Due to implementation to minimize flag space in memory,  
/// there can be flag "collisions" in the bits pertaining to the flag.
/// For example - -@da & -@di map to the same bit. However, this 
/// shouldn't really matter in the long run.
/// A Document detailing what debug flags are acceptable should
/// be available soon.
/// TO USE THE DEBUG MACRO:
/// DEBUGF(flag,code);
/// where flag is the flag that must me turned on for code to be
/// printed
/// @todo Possibly fix implementation to avoid collisions. 
///////////////////////////////////////////////////////////////////////
class Debug {

    //////////////////////////////////////////////////////////////////////
    // PRIVATE FIELD
    //////////////////////////////////////////////////////////////////////
private:

    //////////////////////////////////////////////////////////////////////
    ///@brief The amount of flags we can have, one for each letter of the 
    /// alphabet.
    //////////////////////////////////////////////////////////////////////
    static const int FLAG_COUNT = 26;

    //////////////////////////////////////////////////////////////////////
    ///@brief Number of minor flags for each major. 
    ///@details Currently set to 8, but if more is needed then we can
    /// increase it.
    //////////////////////////////////////////////////////////////////////
    static const int MINOR_FLAGS = 8;

    // 26 (# of letters)  *   8 (Minor flags) = 208 bits = 26 bytes
    using flagset = std::bitset<FLAG_COUNT * MINOR_FLAGS>;
    //////////////////////////////////////////////////////////////////////
    ///@brief Bitset used to keep track of flags turn on and off.
    ///@details flags is a bitset of size 208 bits. This is because
    /// for each major flag (26) there are 8 minor flags. 26*8 = 208 bits
    /// 208 bits = 26 bytes. So our structure for keeping track of
    /// flags is smaller than the space needed for a 32bit integer.
    //////////////////////////////////////////////////////////////////////
    static flagset flags;

    //////////////////////////////////////////////////////////////////////
    ///@brief Private Ctor
    //////////////////////////////////////////////////////////////////////
    Debug();

    //////////////////////////////////////////////////////////////////////
    ///@brief Private function to set wanted flags to true
    ///@param [in] flag The flags to be turned on. The string passed in
    /// by scanOpts will start with a '@' rather than a '-@'
    //////////////////////////////////////////////////////////////////////
    static void setFlags(std::string& flag);

    //////////////////////////////////////////////////////////////////////
    // PUBLIC FIELD
    //////////////////////////////////////////////////////////////////////
public:

    //////////////////////////////////////////////////////////////////////
    ///@brief Scans the command line for optional flag arguments
    ///@param [in] argc Number of arguments from the command line. Is 
    /// always >=1. When flags are entered then argc is always 2. If it is
    /// not 2, then the no flags are ever set. 
    ///@param [in] argv The actual command line arguments. If flags are 
    /// improperly formated, nothing happens.
    //////////////////////////////////////////////////////////////////////
    static void scanOpts(int argc, char** argv);

    //////////////////////////////////////////////////////////////////////
    ///@brief Checks if a flag is set
    ///@param [in] flag The flag that is checked.
    ///@return Returns true of a flag is found to be on. If flag is not
    /// turned on or a improper flag is passed in, then false is returned.
    //////////////////////////////////////////////////////////////////////
    static bool getFlag(std::string flag);

    //////////////////////////////////////////////////////////////////////
    ///@brief A helper function to print the location where the debug
    /// macro is called, when its flag is turned on.
    ///@param [in] flag The flag corresponding to the debug macro.
    ///@param [in] file The file where the marco was called
    ///@param [in] line The line of the file where the macro was called.
    ///@param [in] func The function where the debug macro is called
    //////////////////////////////////////////////////////////////////////
    static void where(std::string flag, const char* file, int line,
        const char* func);

};  //End Debug Class


        //If we are debugging
#ifdef _DEBUG

#include <crtdbg.h>
#include <cstdlib>


#define DBG_INIT() { \
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); \
    }

        //Require Debug Reports at the end of all Executions
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif


        //Make sure new is reported correctly
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif  //DBG_NEW

        //////////////////////////////////////////////////////////////////////
        ///@brief Prints a memory diagnostic to VS Debug output.
        ///@details Since it instantiates a variable temp, it may end up 
        ///     redefining that variable multiple times if used in the same 
        ///     scope. Be careful when using this in the same scope twice.
        //////////////////////////////////////////////////////////////////////
#define MEM_PRINT() {   \
            _CrtMemState temp;  \
            _CrtMemCheckpoint(&temp); \
            _CrtMemDumpStatistics(&temp); \
        }


        //////////////////////////////////////////////////////////////////////
        ///@brief Definition of the debug macro to be used. 
        ///@details TO USE THE DEBUG MACRO: DEBUGF(flag,code);
        /// where flag is the flag that must me turned on for code to be
        /// printed
        //////////////////////////////////////////////////////////////////////
#define DEBUGF(FLAG,CODE) { \
        if (Debug::getFlag (FLAG)) { \
                Debug::where (FLAG, __FILE__, __LINE__, __func__); \
                cout << CODE << endl; \
            } \
        }
#define DEBUGS(FLAG,STMT) { \
            if (Debug::getFlag (FLAG)) { \
                Debug::where (FLAG, __FILE__, __LINE__, __func__); \
                STMT; \
            } \
        }

#else   //If not _DEBUG defined

#define DBG_INIT() ;
#define MEM_PRINT() ;
#define DEBUGF(FLAG,CODE) ;
#define DEBUGS(FLAG,STMT) ;

#endif  // _DEBUG


};      //End namespace ppc


#endif  //End DEBUG_H