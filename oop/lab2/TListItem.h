#ifndef TListItem_H
#define	TListItem_H

#include "Triangle.h"
class TListItem {
public:
	TListItem(Triangle& triangle);
	TListItem(TListItem& orig);
    TListItem* SetRight(TListItem* right);
    TListItem* SetLeft(TListItem* Left);
    TListItem* GetLeft();
    TListItem* GetRight();
    Triangle& GetTriangle();
    
    friend std::ostream& operator<<(std::ostream& os, TListItem& obj);
    
    virtual ~TListItem();
private:
    Triangle triangle;
    TListItem *left;
    TListItem *right;
};

#endif	/* TListItem_H */
