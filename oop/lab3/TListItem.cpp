#include "TListItem.h"
#include <iostream>

TListItem::TListItem(std::shared_ptr<Figure> fig) {
	DEBUG();

    this->fig = fig;
    this->right = nullptr;
    this->left  = nullptr;
    std::cout << "List item: created" << std::endl;
    
    DEBUG();
}

TListItem* TListItem::SetRight(TListItem* ptr) {
	if (right)
		right->left = ptr;
		
	ptr->right = right; 
	ptr->left  = this;
	right = ptr;
	
	DEBUG();
}

TListItem* TListItem::SetLeft(TListItem* ptr) {
	std::cout << "LEFT " << left << std::endl;
	
	DEBUG();
	
	if (left)
		left->right = ptr;
		
	ptr->left  = left;
	ptr->right = this;
	left = ptr;
	
	std::cout << "LEFT " << left << std::endl;
}

std::shared_ptr<Figure> TListItem::GetFigure() {
    return this->fig;
}

TListItem* TListItem::GetRight() {
	DEBUG();
    return right;
}

TListItem* TListItem::GetLeft() {
	DEBUG();
	return left;
}

TListItem::~TListItem() {
	DEBUG();
	std::cout << "List item: deleted" << std::endl;
}

std::ostream& operator<<(std::ostream& os, TListItem& obj) {
	os << "[" << *obj.fig << "]" << std::endl;
	DEBUG();
    return os;
}
