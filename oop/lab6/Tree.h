#ifndef TREE_H
#define TREE_H

#include <iostream>

struct btree {
	btree *left;
	btree *right;
	btree *par;
	void  *val;
};

btree *new_tree (void   *val);
btree *add_child(btree  *tree, void *val);
btree *find_val (btree  *tree, void *val);
void  *del_val  (btree **tree, void *val);
void   t_exterm (btree  *tree);
void   t_print  (btree  *tree, int d, std::ostream& os);

#endif
