#ifndef TLIST_H
#define	TLIST_H
#include <memory>
#include "list_item.h"
#include "iterator.h"
#include "cri.h"

template <class T,class TT> class TList {

public:
    TList();
    
    void InsertSubitem(TT* value);
    void RemoveSubitem(IRemoveCriteria<TT> * criteria);
    void PushBack(T* value);
    bool Remove(T* value);
    size_t Size();
    void Print_sort();
    void Print_thread();
    TIterator<TListItem<T>, T> begin() const;
    TIterator<TListItem<T>, T> end() const;
    template <class A,class AA> friend std::ostream& operator<<(std::ostream& os,const TList<A,AA>& list);
    
    virtual ~TList();
private:
    std::shared_ptr<TListItem<T>> head;
};

#endif
