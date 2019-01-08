#include <cstdlib>
#include <iostream>
#include <memory>

#include "triangle.h"
#include "ttree.h"
#include "list.h"
#include "cri_val.h"
#include "cri_all.h"

int main(int argc, char** argv) {
    TList<TTree<Triangle>,Triangle> list;
    
    list.InsertSubitem(new Triangle(1, 1, 1));
    list.InsertSubitem(new Triangle(2, 1, 1));
    list.InsertSubitem(new Triangle(3, 1, 1));
    list.InsertSubitem(new Triangle(4, 1, 1));
    list.InsertSubitem(new Triangle(5, 1, 1));
    list.InsertSubitem(new Triangle(6, 1, 1));
    list.InsertSubitem(new Triangle(7, 1, 1));
	
	list.Print_sort();
	list.Print_thread();
	
   
    
    IRemoveCriteriaByValue<Triangle> criteria(Triangle(5,1,1));
    IRemoveCriteriaAll<Triangle> criteriaAll;
    list.RemoveSubitem(&criteria);
    

   return 0;
}
