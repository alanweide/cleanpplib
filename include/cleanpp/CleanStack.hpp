//
//  CleanStack.hpp
//  Move Semantics
//
//  Created by Alan Weide on 12/1/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef CleanStack_hpp
#define CleanStack_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

#include "CleanBase.hpp"

namespace cleanpp {
	template <typename T>  // template definition
	class clean_stack: public clean_base<T>
	{
	public:
		clean_stack<T>& operator=(const clean_stack<T>& other) = delete;
		virtual void push(T& x) = 0;
		virtual void pop(T& x) = 0;
		virtual bool isEmpty() const = 0;
	};
}

#endif /* CleanStack_hpp */
