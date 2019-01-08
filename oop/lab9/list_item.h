#ifndef TSTACKITEM_H
#define	TSTACKITEM_H
#include <memory>
#include "triangle.h"
#include "alloc.h"

template<class T> class TListItem {
public:
    TListItem(const std::shared_ptr<T>& triangle);
    template<class A> friend std::ostream& operator<<(std::ostream& os, const TListItem<A>& obj);
    
    std::shared_ptr<TListItem<T>> setNext(std::shared_ptr<TListItem> &next);
    std::shared_ptr<TListItem<T>> getNext();
    std::shared_ptr<TListItem<T>> setPrev(std::shared_ptr<TListItem> &next);
    std::shared_ptr<TListItem<T>> getPrev();
    std::shared_ptr<T> getValue() const;
    void * operator new (size_t size);
    void operator delete(void *p);
    
    void resetPtrs() { if (prev) prev.reset(); }
    
    virtual ~TListItem();
private:
    std::shared_ptr<T> item;
    std::shared_ptr<TListItem<T>> next;
    std::shared_ptr<TListItem<T>> prev;
    
	static TAllocationBlock _allocator;

};

#endif	/* TSTACKITEM_H */

