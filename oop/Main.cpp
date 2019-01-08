#include <cstdlib>
#include <iostream>

#include "Triangle.h"
#include "TListItem.h"
#include "TList.h"

// Simple List on pointers
int main(int argc, char** argv) {
    TList list;
    Triangle t(5, 6, 7);
    Triangle y(9, 9, 9);
    Triangle z(6, 6, 6);
    
    list.addR(t);
	list.addR(y);
    list.addR(z);
    
    std::cout << list << std::endl;
    
    
    return 0;
}
