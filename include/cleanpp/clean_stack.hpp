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

namespace cleanpp {
	template <class T>  // template definition
	class clean_stack: public clean_base<T>
	{
	public:
//        clean_stack<T>(const clean_stack<T> &other) = delete;
//		clean_stack<T>& operator=(const clean_stack<T>& other) = delete;
		virtual void push(T& x) = 0;
		virtual void pop(T& x) = 0;
		virtual bool is_empty() const = 0;
	};
}

#endif /* clean_stack_h */
