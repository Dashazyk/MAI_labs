#ifndef QUADRATE_H
#define QUADRATE_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Quadrate : public Figure {
public :
	Quadrate();
	Quadrate(std::istream &is);
	Quadrate(size_t i);

	double Square() override;
	void Print() override;

	virtual ~Quadrate();

private:
	size_t side_a;
};

#endif  // QUADRATE_H
