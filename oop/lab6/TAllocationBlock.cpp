#include "TAllocationBlock.h"
#include <iostream>
#include "Tree.h"

TAllocationBlock::TAllocationBlock(size_t size,size_t count): _size(size),_count(count)  {
	trfr = new_tree((void *)-1);
	trus = new_tree((void *)-1);
	
	_free_count = _count;
	
    for (size_t i = 0; i < _count; ++i) {
		void *ptr = malloc(_size);
		
		add_child(trfr, ptr);
	}
}

void *get_ptr(btree *tr) {
	void *r = nullptr;
	
	if (tr) {
		if (tr->left && tr->left->val)
			r = tr->left->val;
		else if (tr->right && tr->right->val)
			r = tr->right->val;
	}
	
	return r;
}

void *TAllocationBlock::allocate() {
    void *result = nullptr;
    
	if (_free_count > 0) {
		//result = _free_blocks[_free_count-1];
        result = get_ptr(trfr);
        del_val (&trfr, result);
        add_child(trus, result);
        _free_count--;
        std::cout << "TAllocationBlock: Allocate " << (_count - _free_count) << " of " << _count << std::endl;
    } else 
		std::cout << "TAllocationBlock: No memory exception :-)" << std::endl;
    
    return result;
}

void TAllocationBlock::deallocate(void *pointer) {
	std::cout << "TAllocationBlock: Deallocate block "<< std::endl;

	//_free_blocks[_free_count] = pointer;
	del_val (&trus, pointer);
	add_child(trfr, pointer);
	_free_count++;
}

bool TAllocationBlock::has_free_blocks() {
    return _free_count > 0;
}

TAllocationBlock::~TAllocationBlock() {
    if (_free_count < _count)
		std::cout << "TAllocationBlock: Memory leak?" << std::endl;
	else
		std::cout << "TAllocationBlock: Memory freed" << std::endl;
		
	t_exterm(trfr);
	t_exterm(trus);
	
	free(trfr);
	free(trus);
}
