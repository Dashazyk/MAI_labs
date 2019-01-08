#include <cstdlib>
#include <iostream>
#include <memory>

#include "Rectangle.h"
#include "Triangle.h"
#include "Quadrate.h"
#include "Figure.h"
#include "TList.h"

#include "TAllocationBlock.h"

void TestList()
{
    TList<Figure> list;
    
    list.addRight(std::shared_ptr<Figure>((Figure *)new Triangle(1,1,1)));
    list.addRight(std::shared_ptr<Figure>((Figure *)new Rectangle(2,2)));
    list.addRight(std::shared_ptr<Figure>((Figure *)new Rectangle(3,3)));
    list.addRight(std::shared_ptr<Figure>((Figure *)new Triangle(3,3,3)));

    
    for(auto i : list)  
		std::cout << *i << std::endl;
    
    
    std::shared_ptr<Figure> t;
    
    //while(!list.empty()) std::cout << *list.pop() << std::endl;
}

void TestAllocationBlock() {
   TAllocationBlock allocator(sizeof(int),10);   
   
   int *a1 = nullptr;
   int *a2 = nullptr;
   int *a3 = nullptr;
   int *a4 = nullptr;
   int *a5 = nullptr;
   
   a1 = (int*)allocator.allocate();*a1 = 1; std::cout << "a1 pointer value:" << *a1 << std::endl;
   a2 = (int*)allocator.allocate();*a2 = 2; std::cout << "a2 pointer value:" << *a2 << std::endl;
   a3 = (int*)allocator.allocate();*a3 = 3; std::cout << "a3 pointer value:" << *a3 << std::endl;
   
   allocator.deallocate(a1);
   allocator.deallocate(a3);

   a4 = (int*)allocator.allocate();*a4 = 4; std::cout << "a4 pointer value:" << *a4 << std::endl;
   a5 = (int*)allocator.allocate();*a5 = 5; std::cout << "a5 pointer value:" << *a5 << std::endl;
   std::cout << "a1 pointer value:" << *a1 << std::endl;
   std::cout << "a2 pointer value:" << *a2 << std::endl;
   std::cout << "a3 pointer value:" << *a3 << std::endl;

   allocator.deallocate(a2);
   allocator.deallocate(a4);
   allocator.deallocate(a5);   
}

// templates stack on shared pointer with iterator and allocator on array
int main(int argc, char** argv) {
    
	TestList();
    //TestAllocationBlock();
    
    
    return 0;
}
