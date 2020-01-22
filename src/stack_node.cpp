//
//  stack_node.cpp
//  Cleanpp
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <linked_stack.hpp>

namespace cleanpp {
// ------ BEGIN linked_stack::stack_node ------

template <class T>
linked_stack<T>::stack_node::stack_node(): contents(), next() {}

template <class T>
linked_stack<T>::stack_node::stack_node(stack_node&& other):
contents(std::move(other.contents)),
next(std::move(other.next)) {
    other.clear();
}

template <class T>
typename linked_stack<T>::stack_node& linked_stack<T>::stack_node::operator=(stack_node&& other) {
    if (&other == this) {
        return *this;
    }
    contents = std::move(other.contents);
    next = std::move(other.next);
    other.clear();
}

template <class T>
linked_stack<T>::stack_node::stack_node(T& new_contents):
contents(), next() {
    std::swap(contents, new_contents);
}

// ------ END linked_stack::stack_node ------

}
