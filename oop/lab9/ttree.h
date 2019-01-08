#ifndef TREE_H
#define TREE_H

#include <memory>

template <class T>
class node {
	public:
		T* data;
		node *left;
		node *right;
};

template<class T>
class TTree {
	public:
		TTree();
		~TTree();
		void insert (T* x);
		node<T>* insert(T*, node<T>*);
		
		int size ();
		bool empty();
		
		T* pop();
		
	private:
		int sz;
		node<T> *root;
		
		node<T> *makeEmpty(node<T> *t);
		node<T> *insert (std::shared_ptr<T> x, node<T> *t);
};

#endif
