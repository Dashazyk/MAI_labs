#ifndef TListItem_H
#define	TListItem_H

#include "Figure.h"
#include <memory>

template <class T> class TListItem {
public:
	TListItem(std::shared_ptr<T> fig);
	
	TListItem<T>* SetRight( TListItem<T>* right);
	TListItem<T>* SetLeft ( TListItem<T>* left);
	TListItem<T>* GetLeft ();
	TListItem<T>* GetRight();
    std::shared_ptr<T> GetFigure();
    
    template <class A> friend std::ostream& operator<<(std::ostream& os, TListItem<A>& obj);
    
    virtual ~TListItem();
private:
    std::shared_ptr<T> fig;
	TListItem<T>* left;
	TListItem<T>* right;
};

#endif	/* TListItem_H */
