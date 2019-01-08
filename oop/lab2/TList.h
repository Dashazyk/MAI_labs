#ifndef TLIST_H
#define	TLIST_H

#include "Triangle.h"
#include "TListItem.h"

class TList {
public:
    TList();
    TList(Triangle& tri);
    TList(const TList& orig);
    friend std::ostream& operator<<(std::ostream& os,const TList& list);
    void addL(Triangle &triangle);
    void addR(Triangle &triangle);
    bool empty();
    void del();
    Triangle& getCurrent();
    void moveCurL();
    void moveCurR();
    
    virtual ~TList();
private:
    TListItem *current;
    TListItem *head;
};
#endif	/* TLIST_H */
