#ifndef RECTANGLE_H
#define	RECTANGLE_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Rectangle {
public:
    Rectangle();
    Rectangle(size_t i,size_t j);
    Rectangle(const Rectangle& orig);

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& obj);


    Rectangle& operator=(const Rectangle& right);

    virtual ~Rectangle();
private:
    size_t side_a;
    size_t side_b;
    
};

#endif	/* RECTANGLE_H */
