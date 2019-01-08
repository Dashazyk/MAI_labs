#include "list_item.h"

template <class T> TListItem<T>::TListItem(T* value) {
    _value = std::shared_ptr<T> (value);
    _next = nullptr;
}

template <class T> std::shared_ptr<T> TListItem<T>::GetValue() {
    return _value;
}

template <class T> std::shared_ptr<TListItem<T>> TListItem<T>::GetNext() {
    return _next;
}

template <class T> void TListItem<T>::SetNext(std::shared_ptr<TListItem> next) {
    _next = next;
}

template <class T> void TListItem<T>::PushBack(std::shared_ptr<TListItem> next) {
    if (_next != nullptr) {
        _next->PushBack(next);
    } else {
        _next = next;
    }
}

template <class T> TListItem<T>::~TListItem() {
}

#include "ttree.h"
#include "triangle.h"
template class TListItem<TTree<Triangle>>;
template class TListItem<Triangle>;
