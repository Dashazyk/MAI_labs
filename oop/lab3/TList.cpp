#include "TList.h"

TList::TList() : head(nullptr) {
}

std::ostream& operator<<(std::ostream& os,  TList& List) {
    TListItem* item = List.head;
    
    while (item != nullptr)
    {
		os << "Item: " << *item;
		item = item->GetRight();
    }
    
    return os;
}

void TList::addL(std::shared_ptr<Figure>&& fig){
	TListItem* nitem (new TListItem(fig));
    
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

void TList::addR(std::shared_ptr<Figure>&& fig){
	TListItem* nitem(new TListItem(fig));
    
	if (head == nullptr) {
		head = nitem;
		current = head;
	}
	else
		current->SetRight(nitem);
}

bool TList::empty() {
    return head == nullptr;
}

std::shared_ptr<Figure> TList::del(){
	TListItem* left = current->GetLeft();
	TListItem* right = current->GetRight();
	
	if (left)
		left->SetRight(right);
	else if (right)
		right->SetLeft(left);

	delete current;

	current = left;
	
	return current->GetFigure();
}

void TList::moveCurL() {
	current = current->GetLeft();
}

void TList::moveCurR(){
	current = current->GetRight();
}

std::shared_ptr<Figure> TList::getCurrent(){
	return current->GetFigure();
}

TList::~TList() {
	TListItem* c = head;
	
	std::cerr << "Destructor" << std::endl;
	
	while (c) {
		TListItem* t = c->GetRight();
		delete c;
		c = t;
	}
}
