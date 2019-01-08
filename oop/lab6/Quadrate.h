#ifndef QUADRATE_H
#define QUADRATE_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Quadrate : public Figure {
public :
	Quadrate();
	Quadrate( Quadrate& orig);
	Quadrate(size_t i);

	double Square();
	void print(std::ostream& os);

	friend std::ostream& operator<<(std::ostream& os,  Quadrate& obj);
    

    Quadrate& operator=( Quadrate& right);

    virtual ~Quadrate();

private:
	size_t side_a;
};

#endif  // QUADRATE_H
