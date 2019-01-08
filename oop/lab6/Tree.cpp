#include "Tree.h"

btree *empt_tree(btree *par) {
	btree *tree = new btree;
	
	tree->val = nullptr;
	tree->left = nullptr;
	tree->right = nullptr;
	tree->par = par;
	
	return tree;
}

btree *new_tree (void *val) {
	btree *tree = empt_tree(nullptr);
	
	tree->val = val;
	tree->left = empt_tree(tree);
	tree->right = empt_tree(tree);
	
	return tree;
}

#define DEBUG(x) std::cerr << "DEBUG: " << (x) << "\t :: " << __FUNCTION__ << " : " << __LINE__ << std::endl

btree *add_trchld(btree *tree, btree *chld) {
	btree *ptr = nullptr;
	
	if (tree && chld && chld->val) {
		ptr = add_child(tree, chld->val);
		
		if (ptr && ptr->val) {
			free(ptr->left);
			free(ptr->right);
			
			ptr->left = chld->left;
			ptr->right = chld->right;
		}
	}
	
	return ptr;
}

btree *add_child(btree *tree, void *val) {
	btree *ptr = find_val(tree, val);
	
	if (val && ptr && !ptr->val) {
		ptr->val = val;
		
		ptr->left = empt_tree(ptr);
		ptr->right = empt_tree(ptr);
	}
	
	return ptr;
}

btree *find_val (btree *tree, void *val) {
	btree *ptr = tree;
	
	while (val && ptr && ptr->val && ptr->val != val) {
		if (ptr->val > val)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	
	return ptr;
}

void t_exterm (btree *tree) {
	if (tree) {
		t_exterm(tree->left);
		t_exterm(tree->right);
		
		delete tree;
	}
}

void t_print(btree *tree, int d, std::ostream& os) {
	if (tree && tree->val) {
		for (int i = 0; i < d; ++i)
			os << "|   ";

		os << (long int)tree->val << std::endl;
		
		t_print(tree->left,  d + 1, os);
		t_print(tree->right, d + 1, os);
	}
}

void *del_val(btree **tree, void *val) {
	btree *ptr = find_val(*tree, val);
	
	if (ptr && ptr->val) {
		btree *left = ptr->left;
		btree *right = ptr->right;
		btree *par = ptr->par;
		
		if (par) {
			if (par->left == ptr)
				par->left = empt_tree(par);
			else if (par->right == ptr)
				par->right = empt_tree(par);
				
			add_trchld(par, left);
			add_trchld(par, right);
		}
		else if (right && right->val) {
			*tree = right;
			
			right->par = nullptr;
			
			add_trchld(*tree, left);
		} else if (left && left->val) {
			*tree = left;
			
			left->par = nullptr;
			
			//add_trchld(*tree, right);
		}
		else {
			ptr = nullptr;
			*tree = nullptr;
		}
			
		//std::cerr << "deleting: " << (long int)ptr->val << "\n";
		
		free(ptr);
		free(left);
		free(right);
	}
	
	return ptr ? ptr->val : nullptr;
}
