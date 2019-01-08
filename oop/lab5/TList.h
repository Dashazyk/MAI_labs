#ifndef TSTACK_H
#define	TSTACK_H

#include "TListItem.h"
#include "TIterator.h"
#include "Figure.h"

#include <memory>

template <class T> class TList {
public:
    TList();
    
    void addRight(std::shared_ptr<T> &&item);
    bool empty();
    std::shared_ptr<T> getValue();
    void del();
    
    TIterator<TListItem<T>,T> begin();
    TIterator<TListItem<T>,T> end();
    
    template <class A> friend std::ostream& operator<<(std::ostream& os,const TList<A>& stack);
    virtual ~TList();
    
    void goRight();
    void goLeft ();
    
private:
    std::shared_ptr<TListItem<T>> head;
    std::shared_ptr<TListItem<T>> current;
};

#endif	/* TSTACK_H */
