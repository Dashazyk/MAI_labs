#include <cstdlib>
#include <iostream>
#include <memory>

#include "Rectangle.h"
#include "Quadrate.h"
#include "Triangle.h"
#include "TList.h"


// template list on shared_ptr with iterator
int main(int argc, char** argv) {
    
    TList<Figure> list;
    
    list.addRight(std::shared_ptr<Figure>((Figure *)new Triangle(1,1,1)));
    list.addRight(std::shared_ptr<Figure>((Figure *)new Rectangle(2,2)));
    list.addRight(std::shared_ptr<Figure>((Figure *)new Quadrate(3)));
    
    list.goRight();
    
    list.addRight(std::shared_ptr<Figure>((Figure *)new Triangle(4,4,4)));
    
  //  list.goLeft();
    
    list.del();
    
    for(auto i : list)
		std::cout << *i << std::endl;
    
    return 0;
}
