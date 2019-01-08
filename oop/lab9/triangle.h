#ifndef TRIANGLE_H
#define	TRIANGLE_H

#include <cstdlib>
#include <iostream>

class Triangle {
public:
    Triangle();
    Triangle(size_t i,size_t j,size_t k);
    Triangle(const Triangle& orig);

    friend std::ostream& operator<<(std::ostream&  os, const Triangle& obj);
    friend int  operator> (const Triangle& l, const Triangle& r);
    friend int  operator< (const Triangle& l, const Triangle& r);

    bool operator==(const Triangle& other);
    Triangle& operator=(const Triangle& right);
    
    int square() const;

    virtual ~Triangle();
private:
    size_t side_a;
    size_t side_b;
    size_t side_c;
};

#endif
