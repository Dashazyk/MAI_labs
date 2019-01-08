#ifndef FIGURE_H
#define	FIGURE_H

#include <iostream>

#define DEBUG();
// #define DEBUG() std::cerrв << "\tDEBUG: " << __FILE__ << ":\t" << __FUNCTION__ << "(): \t" << __LINE__ << std::endl;

class Figure {
public:
	virtual double Square() = 0;
    virtual void   print(std::ostream& os) = 0;
	friend std::ostream& operator<<(std::ostream& os, Figure& obj){
		obj.print(os);
	}

};

#endif	/* FIGURE_H */
