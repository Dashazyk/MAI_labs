#include "Rectangle.h"
#include <iostream>
#include <cmath>

Rectangle::Rectangle() : Rectangle(0, 0) {
}
Rectangle::Rectangle(size_t i, size_t j) :side_a(i), side_b(j) {
	std::cout << "Rectangle created: " << side_a << ", "<< side_b << std::endl;
}

Rectangle::Rectangle( Rectangle& orig) {
	std::cout << "Rectangle copy created" << std::endl;
    side_a = orig.side_a;
    side_b = orig.side_b;
}

double Rectangle::Square() {
	return double (side_a) * double (side_b) ;
}

Rectangle& Rectangle::operator=( Rectangle& right) {
	std::cout << "Rectangle copied" << std::endl;
    side_a = right.side_a;
    side_b = right.side_b;
	return *this;
}

Rectangle::~Rectangle() {
	std::cerr << "Deleting: " << std::endl;
	print(std::cerr);
	std::cerr << "\n";
	std::cout << "Rectangle deleted" << std::endl;
}

void Rectangle::print(std::ostream& os) {
	os << "a=" << side_a << ", b=" << side_b;
}

std::ostream& operator<<(std::ostream& os, Rectangle& obj) {
	obj.print(os);
	return os;
}
