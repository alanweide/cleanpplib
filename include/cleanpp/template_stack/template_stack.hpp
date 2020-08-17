//
//  template_stack.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/5/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef template_stack_h
#define template_stack_h

#include <stdio.h>
#include <clean_base.hpp>
#include <clean_stack/clean_stack.hpp>

namespace cleanpp {

template<template<typename> class I, typename Item>
class t_stack: public clean_base {
private:
    std::unique_ptr<stack<Item>> rep_;
public:
    t_stack() {
        rep_ = std::make_unique<I<Item>>();
    }
    
    t_stack(const t_stack<I, Item> &o) = delete;
    t_stack(t_stack<I, Item>&& o): rep_(std::move(o.rep_)) {
		o.rep_ = std::make_unique<I<Item>>();
    }
    
    t_stack<I, Item>& operator=(const t_stack<I, Item>& o) = delete;
    t_stack<I, Item>& operator=(t_stack<I, Item>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<I<Item>>();
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
    bool operator==(t_stack<I, Item>& other) {
        return *this->rep_ == *other.rep_;
    }
    
    friend std::ostream& operator<<(std::ostream& out, t_stack<I, Item>& o) {
        return out << *o.rep_;
    }
};
}

#endif /* template_stack_h */
