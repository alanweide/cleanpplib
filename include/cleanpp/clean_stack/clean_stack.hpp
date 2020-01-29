//
//  clean_stack.hpp
//  Move Semantics
//
//  Created by Alan Weide on 12/1/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef clean_stack_h
#define clean_stack_h

#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>

#include "linked_stack.hpp"

namespace cleanpp {
	template <class T>
	class clean_stack: public clean_base
	{
	public:
//        clean_stack<T>(const clean_stack<T> &other) = delete;
//		clean_stack<T>& operator=(const clean_stack<T>& other) = delete;
		virtual void push(T& x) = 0;
		virtual void pop(T& x) = 0;
		virtual bool is_empty() const = 0;
        
        bool operator==(clean_stack<T> &other) {
            bool ans;
            if (is_empty() && other.is_empty()) {
                ans = true;
            } else if (is_empty() != other.is_empty()) {
                ans = false;
            } else {
                T this_top, other_top;
                pop(this_top);
                other.pop(other_top);
                ans = *this == other;
                push(this_top);
                other.push(other_top);
            }
            return ans;
        }
        
	};
}

#endif /* clean_stack_h */
