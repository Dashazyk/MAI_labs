#include "TList.h"

template <class T> TList<T>::TList() : head(nullptr) {
}

template <class T> std::ostream& operator<<(std::ostream& os,  TList<T>& List) {
    TListItem<T>* item = List.head;
    
    while (item != nullptr)
    {
		os << "Item: " << *item;
		item = item->GetRight();
    }
    
    return os;
}

template <class T> void TList<T>::addL(std::shared_ptr<T>&& fig){
	TListItem<T>* nitem (new TListItem<T>(fig));
    
	if (head == nullptr){
		head = nitem;
		current = head;
	}
	else
		current->SetLeft(nitem);
		
	while (head->GetLeft())
		head = head->GetLeft();
		
	DEBUG();
}

template <class T> void TList<T>::addR(std::shared_ptr<T>&& fig){
	TListItem<T>* nitem(new TListItem<T>(fig));
    
	if (head == nullptr) {
		head = nitem;
		current = head;
	}
	else
		current->SetRight(nitem);
}

template <class T> bool TList<T>::empty() {
    return head == nullptr;
}

template <class T> std::shared_ptr<T> TList<T>::del(){
	TListItem<T>* left = current->GetLeft();
	TListItem<T>* right = current->GetRight();
	
	if (left)
		left->SetRight(right);
	else if (right)
		right->SetLeft(left);

	delete current;

	current = left;
	
	return current->GetFigure();
}

template <class T> void TList<T>::moveCurL() {
	current = current->GetLeft();
}

template <class T> void TList<T>::moveCurR(){
	current = current->GetRight();
}

template <class T> std::shared_ptr<T> TList<T>::getCurrent(){
	return current->GetFigure();
}

template <class T> TList<T>::~TList() {
	TListItem<T>* c = head;
	
	std::cerr << "Destructor" << std::endl;
	
	while (c) {
		TListItem<T>* t = c->GetRight();
		delete c;
		c = t;
	}
}

#include "Figure.h"
template class TList<Figure>;
template std::ostream& operator<<(std::ostream& os,  TList<Figure>& stack);









