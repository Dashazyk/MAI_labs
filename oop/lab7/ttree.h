#ifndef TREE_H
#define TREE_H

#include <memory>

template <class T>
class node {
	public:
		std::shared_ptr<T> data;
		node *left;
		node *right;
};

template<class T>
class TTree {
	public:
		TTree();
		~TTree();
		void insert (std::shared_ptr<T> x);
		void insert (T *x);
		void remove (std::shared_ptr<T> x);
		void display();
		void search (std::shared_ptr<T> x);
		std::ostream& print(std::ostream& os);
		
		int size ();
		int empty();
		
		std::shared_ptr<T> getHeadValue();
		std::shared_ptr<T> pop();

	private:
		int sz;
		std::ostream& rec_print(node<T> *root, std::ostream& os, int d);
		node<T> *root;
		
		node<T> *makeEmpty(node<T> *t);
		node<T> *insert (std::shared_ptr<T> x, node<T> *t);
		node<T> *findMin (node<T> *t);
		node<T> *findMax (node<T> *t);
		node<T> *remove (std::shared_ptr<T> x, node<T> *t);
		void inorder (node<T> *t);
		node<T> *find (node<T> *t, std::shared_ptr<T> x);
};

#endif
