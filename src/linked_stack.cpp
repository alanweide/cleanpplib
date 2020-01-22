//
//  linked_stack.cpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <linked_stack.hpp>
#include "stack_node.cpp"

namespace cleanpp {

template <class T>
linked_stack<T>::linked_stack() { }

template <class T>
linked_stack<T>::linked_stack(linked_stack<T>&& other):
top_ptr_(std::move(other.top_ptr_)) {
    other.clear();
}

template <class T>
linked_stack<T>& linked_stack<T>::operator=(linked_stack<T>&& other) {
    if (&other == this) {
        return *this;
    }
    
    top_ptr_ = std::move(other.top_ptr_);
    other.clear();
}

template <class T>
void linked_stack<T>::clear() {
    top_ptr_.reset();
}

template <class T>
void linked_stack<T>::push(T& x) {
    auto new_top = std::make_unique<stack_node>(x);
    std::swap(new_top->next, top_ptr_);
    std::swap(top_ptr_, new_top);
}

template <class T>
void linked_stack<T>::pop(T& x) {
    std::swap(x, top_ptr_->contents);
    std::swap(top_ptr_, top_ptr_->next);
}

template <class T>
bool linked_stack<T>::is_empty() const {
    return top_ptr_ == nullptr;
}

template <class T>
std::ostream& linked_stack<T>::print(std::ostream& out) {
    out << "<";
    linked_stack<T> temp{};
    while (!is_empty())
    {
        T top;
        pop(top);
        out << top;
        if (!is_empty())
        {
            out << ", ";
        }
        temp.push(top);
    }
    while (!temp.isEmpty()) {
        T top;
        temp.pop(top);
        push(top);
    }
    out << ">";
    return out;
}
}
