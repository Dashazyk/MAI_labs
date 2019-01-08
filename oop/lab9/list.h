#ifndef TSTACK_H
#define	TSTACK_H

#include "list_item.h"
#include "iterator.h"
#include "triangle.h"

#include <memory>

template <class T> class TList {
public:
    TList();
    
    void addRight(std::shared_ptr<T> &&item);
    bool empty();
    std::shared_ptr<T> getValue();
    std::shared_ptr<T> del();
    
    // printList () const;
    
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
