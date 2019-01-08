#ifndef TListItem_H
#define	TListItem_H

#include "Figure.h"
#include <memory>

class TListItem {
public:
	TListItem(std::shared_ptr<Figure> fig);
	
	TListItem* SetRight( TListItem* right);
	TListItem* SetLeft ( TListItem* left);
	TListItem* GetLeft ();
	TListItem* GetRight();
    std::shared_ptr<Figure> GetFigure();
    
    friend std::ostream& operator<<(std::ostream& os, TListItem& obj);
    
    virtual ~TListItem();
private:
    std::shared_ptr<Figure> fig;
	TListItem* left;
	TListItem* right;
};

#endif	/* TListItem_H */
