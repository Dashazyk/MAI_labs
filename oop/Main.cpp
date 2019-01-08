#include <cstdlib>
#include <iostream>
#include <memory>

#include "Rectangle.h"
#include "Quadrate.h"
#include "Triangle.h"
#include "TListItem.h"
#include "TList.h"

int main(int argc, char** argv) {
    TList list;
    
    list.addR(std::shared_ptr<Figure>(new Triangle(5, 6, 7)));
    list.addR(std::shared_ptr<Figure>(new Quadrate(3)));
	list.addR(std::shared_ptr<Figure>(new Rectangle(4, 8)));
	
    std::cout << list;
    
    //list.del();
   
    return 0;
}

