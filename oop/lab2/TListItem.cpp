#include "TListItem.h"
#include <iostream>

TListItem::TListItem(Triangle& triangle) {
    this->triangle = triangle;
    this->right = nullptr;
    this->left = nullptr;
    std::cout << "List item: created" << std::endl;
}

TListItem::TListItem(TListItem& orig) {
    this->triangle = orig.triangle;
    this->right = orig.right;
    this->left  = orig.left;
    std::cout << "List item: copied" << std::endl;
}

TListItem* TListItem::SetRight(TListItem* ptr) {
	if (right)
		right->left = ptr;
		
	ptr->right = right;
	ptr->left = this;
	right = ptr;
}

TListItem* TListItem::SetLeft(TListItem *ptr) {
	std::cout << "LEFT " << left << std::endl;
	
	if (left)
		left->right = ptr;
		
	ptr->left = left;
	ptr->right = this;
	left = ptr;
	
	std::cout << "LEFT " << left << std::endl;
}

Triangle& TListItem::GetTriangle() {
    return this->triangle;
}

TListItem* TListItem::GetRight() {
    return right;
}

TListItem* TListItem::GetLeft() {
	return left;
}

TListItem::~TListItem() {
	std::cout << "List item: deleted" << std::endl;
}

std::ostream& operator<<(std::ostream& os, TListItem& obj) {
	os << "[" << obj.triangle << "]" << std::endl;
    return os;
}
