#ifndef TLIST_H
#define	TLIST_H

#include "Figure.h"
#include "TListItem.h"
#include <memory>

template <class T> class TList {
public:
    TList();
    
    template <class A> friend std::ostream& operator<<(std::ostream& os, TList<A>& list);
    void addL(std::shared_ptr<T>&& fig);
    void addR(std::shared_ptr<T>&& fig);
    bool empty();
    std::shared_ptr<T> del();
    std::shared_ptr<T> getCurrent();
    void moveCurL();
    void moveCurR();
    
    virtual ~TList();
private:
    TListItem<T>* current;
    TListItem<T>* head;
};
#endif	/* TLIST_H */
