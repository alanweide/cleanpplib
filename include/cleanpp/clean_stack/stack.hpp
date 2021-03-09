//
//  flexible_stack.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/5/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef flexible_stack_h
#define flexible_stack_h

#include <stdio.h>
#include "clean_base.hpp"
#include "stack_impl.hpp"
#include "array_stack.hpp"

namespace cleanpp {

template<typename Item>
class stack: public clean_base {
protected:
    template <typename I>
    using _flex_stack_def_t = array_stack<I>;
    static_assert(std::is_base_of<stack_impl<int>, _flex_stack_def_t<int>>::value,
                  "_flex_stack_def_t must derive from stack<Item>");
    

    std::unique_ptr<stack_impl<Item>> rep_;
public:
	stack() : rep_(std::make_unique<_flex_stack_def_t<Item>>()) {
    }
    
	template<template<typename> class I>
	stack(__attribute__((unused)) const I<Item>& impl): rep_(std::make_unique<I<Item>>()) {
		static_assert(std::is_base_of<stack_impl<Item>, I<Item>>::value,
					  "Template parameter I must derive from stack<Item>");
	}
	
    stack(const stack<Item> &o) = delete;
    stack(stack<Item>&& o): rep_(std::move(o.rep_)) {
		o.rep_ = std::make_unique<_flex_stack_def_t<Item>>();
    }
    
    stack<Item>& operator=(const stack<Item>& o) = delete;
    stack<Item>& operator=(stack<Item>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<_flex_stack_def_t<Item>>();
		return *this;
    }
    
    void clear() {
		this->rep_->clear();
    }
    
    /*
     updates this
     clears  x
     ensures this = <#x> * #this
     */
    virtual void push(Item&& x) {
        rep_->push(std::forward<Item>(x));
    }
    
    /*
     updates  this
     replaces x
     requires |this| > 0
     ensures  #this = <x> * this
     */
    virtual Item pop() {
        return rep_->pop();
    }
    
    /*
     ensures is_empty = (|this| = 0)
     */
    virtual bool is_empty() const {
        return rep_->is_empty();
    }
    
    /*
     ensures `==` = (this = other)
     */
    bool operator==(stack<Item>& other) {
        return *this->rep_ == *other.rep_;
    }
    
    friend std::ostream& operator<<(std::ostream& out, stack<Item>& o) {
        return out << *o.rep_;
    }
};
}

#endif /* flexible_stack_h */
