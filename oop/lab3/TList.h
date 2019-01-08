#ifndef TLIST_H
#define	TLIST_H

#include "Figure.h"
#include "TListItem.h"
#include <memory>

class TList {
public:
    TList();
    
    friend std::ostream& operator<<(std::ostream& os, TList& list);
    void addL(std::shared_ptr<Figure>&& fig);
    void addR(std::shared_ptr<Figure>&& fig);
    bool empty();
    std::shared_ptr<Figure> del();
    std::shared_ptr<Figure> getCurrent();
    void moveCurL();
    void moveCurR();
    
    virtual ~TList();
private:
    TListItem* current;
    TListItem* head;
};
#endif	/* TLIST_H */
