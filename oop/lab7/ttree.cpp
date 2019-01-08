#include <iostream>
#include "ttree.h"

template<class T> 
int TTree<T>::size () {
	return sz;
}

template<class T> 
int TTree<T>::empty() {
	return sz == 0;
}

template<class T> 		
std::shared_ptr<T> TTree<T>::getHeadValue() {
	return root->data;
}

template<class T> 
std::shared_ptr<T> TTree<T>::pop() {
	std::shared_ptr<T> res = root->data;
	
	remove(res);
	
	return res;
}

template<class T> 
node<T> * TTree<T>::makeEmpty(node<T> *t) {
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
node<T> * TTree<T>::insert(std::shared_ptr<T> x, node<T> *t) {
	if (t == NULL) {
		t = new node<T>;
		t->data = x;
		t->left = t->right = NULL;
	}
	else if (*x < *t->data)
		t->left = insert(x, t->left);
	else if (*x > *t->data)
		t->right = insert(x, t->right);
		
	return t;
}

template<class T> 
node<T> * TTree<T>::findMin(node<T> *t)
{
	if (t == NULL)
		return NULL;
	else if (t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

template<class T> 
node<T> * TTree<T>::findMax(node<T> *t) {
	if (t == NULL)
		return NULL;
	else if (t->right == NULL)
		return t;
	else
		return findMax(t->right);
}

template<class T> 
node<T> * TTree<T>::remove(std::shared_ptr<T> x, node<T> *t) {
	node<T> *temp;
	
	sz--;
	
	if (sz < 0)
		sz = 0;
		
	if (t == NULL)
		;
	else if (*x < *t->data)
		t->left = remove(x, t->left);
	else if (*x > *t->data)
		t->right = remove(x, t->right);
	else if (t->left && t->right) {
		temp = findMin(t->right);
		t->data  = temp->data;
		t->right = remove(t->data, t->right);
	}
	else {
		temp = t;
		if (t->left == NULL)
			t = t->right;
		else if (t->right == NULL)
			t = t->left;
		delete temp;
	}

	return t;
}

template<class T> 
void TTree<T>::inorder(node<T> *t) {
	if (t == NULL)
		return;
	inorder(t->left);
	std::cout << *t->data << " ";
	inorder(t->right);
}

template<class T> 
node<T> * TTree<T>::find(node<T> *t, std::shared_ptr<T> x) {
	if (t == NULL)
		return NULL;
	else if (*x < *t->data)
		return find(t->left, x);
	else if (*x > *t->data)
		return find(t->right, x);
	else
		return t;
}

template<class T> 
TTree<T>::TTree() {
	root = NULL;
	sz   = 0;
}

template<class T> 
TTree<T>::~TTree() {
	root = makeEmpty(root);
}

template<class T> 
void TTree<T>::insert(std::shared_ptr<T> x) {
	sz++;
	std::cout << "SIZE = " << sz << std::endl;
	root = insert(x, root);
}

template<class T> 
void TTree<T>::insert(T *x) {
	std::shared_ptr<T> p(x);
	sz++;
	std::cout << "SIZE = " << sz << std::endl;
	root = insert(p, root);
}

template<class T> 
void TTree<T>::remove(std::shared_ptr<T> x) {
	root = remove(x, root);
}

template<class T> 
void TTree<T>::display() {
	inorder(root);
	std::cout << std::endl;
}

template<class T> 
std::ostream& TTree<T>::print(std::ostream& os) {
	return rec_print(root, os, 0);
}

template<class T> 
std::ostream& TTree<T>::rec_print(node<T> *root, std::ostream& os, int d) {
	if (root) {
		for (int i = 0; i < d; ++i)
			//os << "|---";
			os << "|--";
			
		if (root && root->data)
			os << *root->data;
			
		os << std::endl;
			
		rec_print(root->left,  os, d + 1);
		rec_print(root->right, os, d + 1);
	}
	
	return os;
}

template<class T> 
void TTree<T>::search(std::shared_ptr<T> x) {
	root = find(root, x);
}

#include "triangle.h"
template class TTree<int>;
template class TTree<Triangle>;
