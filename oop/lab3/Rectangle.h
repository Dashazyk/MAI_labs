#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Rectangle : public Figure {
public :
	Rectangle();
	Rectangle( Rectangle& orig);
	Rectangle(size_t i, size_t j);

	double Square();
	void print(std::ostream& os);

	friend std::ostream& operator<<(std::ostream& os,  Rectangle& obj);
    

    Rectangle& operator=( Rectangle& right);

    virtual ~Rectangle();

private:
	size_t side_a;
	size_t side_b;
};

#endif  // RECTANGLE_H
