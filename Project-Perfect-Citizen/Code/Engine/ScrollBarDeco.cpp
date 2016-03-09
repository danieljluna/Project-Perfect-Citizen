#include "ScrollBarDeco.h"

using namespace ppc;

ScrollBarDecorator::ScrollBarDecorator(WindowInterface& win) : 
        WindowDecorator(win) {

}




ScrollBarDecorator::ScrollBarDecorator(WindowInterface& win, 
                                       sf::FloatRect& view) :
        WindowDecorator(win) {
    
    barSize_ = 0.2f;
    
}