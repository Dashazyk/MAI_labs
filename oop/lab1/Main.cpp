#include <cstdlib>
#include "Triangle.h"
#include "Quadrate.h"
#include "Rectangle.h"

int main(int argc, char** argv) {

    Figure *ptr = new Triangle(std::cin);
    ptr->Print();
    std::cout << "Rectangle square: ";
    std::cout << ptr->Square() << std::endl;
    delete ptr;
    
    Figure *qdr = new Quadrate(std::cin);
    qdr->Print();
    std::cout << "Rectangle square: ";
    std::cout << qdr->Square() << std::endl;
    delete qdr;
    
    Figure *rtg = new Rectangle(std::cin);
    rtg->Print();
    std::cout << "Rectangle square: ";
    std::cout << rtg->Square() << std::endl;
    delete rtg;
    
    return 0;
}
