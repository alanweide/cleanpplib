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
#include <clean_base.hpp>
#include <stack_impls/stack_impl.hpp>
#include <stack_impls/array_stack.hpp>

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

    /**
	 * @brief no argument constructor
	 * 
	 * @ensures this = <>
	 */
	stack() : rep_(std::make_unique<_flex_stack_def_t<Item>>()) {
    }
    
	template<template<typename> class I>
	stack(__attribute__((unused)) const I<Item>& impl): rep_(std::make_unique<I<Item>>()) {
		static_assert(std::is_base_of<stack_impl<Item>, I<Item>>::value,
					  "Template parameter I must derive from stack<Item>");
	}
	
    stack(const stack<Item> &o) = delete;

    /**
	 * @brief Custom move constructor
	 * 
	 * @param other - the stack being moved from
	 */
    stack(stack<Item>&& o): rep_(std::move(o.rep_)) {
		o.rep_ = std::make_unique<_flex_stack_def_t<Item>>();
    }
    
    stack<Item>& operator=(const stack<Item>& o) = delete;

    /**
     * @brief custom move assignment operator
     * 
     * @param other - the stack being moved from
     * @return the newly-assigned this
     * @ensures this = #other
     */
    stack<Item>& operator=(stack<Item>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<_flex_stack_def_t<Item>>();
		return *this;
    }
    
    /**
     * @brief clears this
     */
    void clear() {
		this->rep_->clear();
    }
    
    /**
     * @brief Adds x to the top of this  
     *  
     * @param x - the entry to be aded
     * @ensures this = <x> * #this
     */
    virtual void push(Item&& x) {
        rep_->push(std::forward<Item>(x));
    }

    /**
     * @brief Removes x from the top of this
     * 
     * @return the entry rmemoved
     * @requires this /= <>
     * @ensures #this = <pop> * this
     */
    virtual Item pop() {
        return rep_->pop();
    }
    

    /**
     * @brief Reports whether this is empty
     * 
     * @return true iff |this| = 0
     * @ensures is_empty = (|this| = 0)
     */
    virtual bool is_empty() const {
        return rep_->is_empty();
    }


    /**
     * @brief overloaded equality operator
     * 
     * @param other - stack to compare with
     * @return true iff this = other
     * @ensures '==' = (this = other)
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
