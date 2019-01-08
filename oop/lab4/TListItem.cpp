#include "TListItem.h"
#include <iostream>

template <class T> TListItem<T>::TListItem(std::shared_ptr<T> fig) {
	DEBUG();

    this->fig = fig;
    this->right = nullptr;
    this->left  = nullptr;
    std::cout << "List item: created" << std::endl;
    
    DEBUG();
}

template <class T> TListItem<T>* TListItem<T>::SetRight(TListItem<T>* ptr) {
	if (right)
		right->left = ptr;
		
	ptr->right = right; 
	ptr->left  = this;
	right = ptr;
	
	DEBUG();
}

template <class T> TListItem<T>* TListItem<T>::SetLeft(TListItem<T>* ptr) {
	std::cout << "LEFT " << left << std::endl;
	
	DEBUG();
	
	if (left)
		left->right = ptr;
		
	ptr->left  = left;
	ptr->right = this;
	left = ptr;
	
	std::cout << "LEFT " << left << std::endl;
}

template <class T> std::shared_ptr<T> TListItem<T>::GetFigure() {
    return this->fig;
}

template <class T> TListItem<T>* TListItem<T>::GetRight() {
	DEBUG();
    return right;
}

template <class T> TListItem<T>* TListItem<T>::GetLeft() {
	DEBUG();
	return left;
}

template <class T> TListItem<T>::~TListItem() {
	DEBUG();
	std::cout << "List item: deleted" << std::endl;
}

template <class A> std::ostream& operator<<(std::ostream& os, TListItem<A>& obj) {
	os << "[" << *obj.fig << "]" << std::endl;
	DEBUG();
    return os;
}

#include "Figure.h"
template class TListItem<Figure>;
template std::ostream& operator<<(std::ostream& os, TListItem<Figure>& obj);



