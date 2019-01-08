#include <iostream>
#include "ttree.h"

template<class T>
TTree<T>::TTree() {
	sz = 0;
	root = nullptr;
}

template<class T> 
int TTree<T>::size () {
	return sz;
}

template<class T> 
bool TTree<T>::empty() {
	return root == NULL;
}

template<class T> 
T* TTree<T>::pop() {
	T* other;
	if(root->right) {
		other = root->data;
		root->data = root->right->data;
		free(root->right);
		root->right = NULL;
		return other;
	}
	else if (root->left) {
		node<T>* tmp = root->left;
		other = root->data;
		root->data = root->left->data;
		root->right = root->left->right;
		root->left = root->left->left;
		free(tmp);
		return other;
	}
	else {
		other = root->data;
		free(root);
		root = NULL;
		return other;
	}
}

template<class T> 
node<T>* TTree<T>::makeEmpty(node<T> *t) {
	if (t == NULL)
		;
	else {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	return NULL;
}

template<class T> 
node<T>* TTree<T>::insert(T* x, node<T> *t) {
	if (t == NULL) {
		t = new node<T>;
		t->data = x;
		t->left = nullptr;
		t->right = nullptr;
		return t;
	}
	if(!t->right) {
		t->right = insert(x, t->right);
	}
	else {
		t->left = insert(x, t->left);
	}
	return t;
}

template<class T> 
TTree<T>::~TTree() {
	makeEmpty(root);
}

template<class T> 
void TTree<T>::insert(T* x) {
	root = insert(x, root);
}


#include "triangle.h"
template class TTree<int>;
template class TTree<Triangle>;

#include <functional>
template class TTree<std::function<void(void)>>;
