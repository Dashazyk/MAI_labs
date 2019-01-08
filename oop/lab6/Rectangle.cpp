#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle() : Rectangle(0, 0) {
    std::cout << "Rectangle created: default" << std::endl;
}

Rectangle::Rectangle(size_t i, size_t j) : side_a(i), side_b(j) {
    std::cout << "Rectangle created: " << side_a << ", " << side_b << std::endl;
}

Rectangle::Rectangle(const Rectangle& orig) {
    std::cout << "Rectangle copy created" << std::endl;
    side_a = orig.side_a;
    side_b = orig.side_b;
}

Rectangle& Rectangle::operator=(const Rectangle& right) {

    if (this == &right) return *this; 
    
    std::cout << "Rectangle copied" << std::endl;
    side_a = right.side_a;
    side_b = right.side_b;
    
    return *this;
}

Rectangle::~Rectangle() {
    std::cout << "Rectangle deleted" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& obj) {
    os << "a=" << obj.side_a << ", b=" << obj.side_b;
    return os;
}
