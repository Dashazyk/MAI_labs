#ifndef TRIANGLE_H
#define	TRIANGLE_H

#include <iostream>
#include "Figure.h"

class Triangle : public Figure {
public:
    Triangle();
    Triangle(size_t i,size_t j,size_t k);
    Triangle( Triangle& orig);

    double Square();
    void print(std::ostream& os);
    
	friend std::ostream& operator<<(std::ostream& os,  Triangle& obj);
    

    Triangle& operator=( Triangle& right);

    virtual ~Triangle();
private:
    size_t side_a;
    size_t side_b;
    size_t side_c;
};

#endif	/* TRIANGLE_H */
