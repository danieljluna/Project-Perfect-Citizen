#include "LoggerParcel.h"

using namespace ppc;

LoggerParcel::operator std::string() const {
     std::string result;

     switch (type) {
     case LoggerParcel::Number:
         result = std::to_string(number);
         break;
     case LoggerParcel::Timer:
         result = std::to_string(time.asSeconds());
         break;
     }

     return result;
};
