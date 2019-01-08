#include "TList.h"

TList::TList() : head(nullptr) {
}

TList::TList(const TList& orig) {
    head = orig.head;
}

std::ostream& operator<<(std::ostream& os, const TList& List) {
    TListItem *item = List.head;
    
    while(item!=nullptr)
    {
		os << *item;
		item = item->GetRight();
    }
    
    return os;
}

void TList::addL(Triangle &triangle){
	TListItem *nitem = new TListItem(triangle);
    
	if (head == nullptr){
		head = nitem;
		current = head;
	}
	else
		current->SetLeft(nitem);
		
	while (head->GetLeft())
		head = head->GetLeft();
}

void TList::addR(Triangle &triangle){
	TListItem *nitem = new TListItem(triangle);
    
	if (head == nullptr){
		head = nitem;
		current = head;
	}
	else
		current->SetRight(nitem);
}

bool TList::empty() {
    return head == nullptr;
}

void TList::del(){
	TListItem *left = current->GetLeft();
	TListItem *right = current->GetRight();
	
	if (left)
		left->SetRight(right);
	else if (right)
		right->SetLeft(left);

	delete current;

	current = left;
}

void TList::moveCurL(){
	current = current->GetLeft();
}

void TList::moveCurR(){
	current = current->GetRight();
}

Triangle& TList::getCurrent(){
	return current->GetTriangle();
}

TList::~TList() {
	TListItem *c = head;
	
	while (c) {
		TListItem *t = c->GetRight();
		delete c;
		c = t;
	}
}
