#include "triangle.h"
#include <iostream>

Triangle::Triangle() : Triangle(0, 0, 0) {
    std::cout << "Triangle created: default" << std::endl;
}

Triangle::Triangle(size_t i, size_t j, size_t k) : side_a(i), side_b(j), side_c(k) {
    std::cout << "Triangle created: " << side_a << ", " << side_b << ", " << side_c << std::endl;
}

Triangle::Triangle(const Triangle& orig) {
    std::cout << "Triangle copy created" << std::endl;
    side_a = orig.side_a;
    side_b = orig.side_b;
    side_c = orig.side_c;
}

bool Triangle::operator==(const Triangle& other){
    return (side_a==other.side_a)&&(side_b==other.side_b)&&(side_c==other.side_c);
}
Triangle& Triangle::operator=(const Triangle& right) {

    if (this == &right) 
		return *this; 
    
    std::cout << "Triangle copied" << std::endl;
    side_a = right.side_a;
    side_b = right.side_b;
    side_c = right.side_c;
    
    return *this;
}

Triangle::~Triangle() {
    std::cout << "Triangle deleted" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Triangle& obj) {

    os << "a=" << obj.side_a << ", b=" << obj.side_b << ", c=" << obj.side_c;
    return os;
}

int operator> (const Triangle& l, const Triangle& r) {
	return l.square() > r.square();
}

int operator< (const Triangle& l, const Triangle& r) {
	return l.square() < r.square();
}

int Triangle::square() const {
	return side_a * side_b * side_c;
}
