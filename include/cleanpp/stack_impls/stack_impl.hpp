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

#include "clean_base.hpp"

namespace cleanpp {

template <class T>
class stack_impl: public clean_base {
    /*
     stack is modeled by string of T
     */
private:
	virtual std::string to_str() = 0;
public:
    
    /*
     updates this
     clears  x
     ensures this = <#x> * #this
     */
	virtual void push(T&& x) = 0;
    
    /*
     updates  this
     requires |this| > 0
     ensures  #this = <pop> * this
     */
	virtual T pop() = 0;
    
    /*
     ensures is_empty = (|this| = 0)
     */
	virtual bool is_empty() const = 0;
	
    /*
     ensures `==` = (this = other)
     */
	bool operator==(stack_impl<T> &other) {
		bool ans;
		if (is_empty() && other.is_empty()) {
			ans = true;
		} else if (is_empty() != other.is_empty()) {
			ans = false;
		} else {
			T this_top, other_top;
			pop(this_top);
			other.pop(other_top);
			ans = (*this == other);
			push(this_top);
			other.push(other_top);
		}
		return ans;
	}
	
	friend std::ostream& operator<<(std::ostream& out, stack_impl<T>& o) {
		return out << o.to_str();
	}
};
	
}

#endif /* clean_stack_h */
