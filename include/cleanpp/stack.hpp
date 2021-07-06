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
#include <stack_impl/stack_impl.hpp>
#include <stack_impl/array_stack.hpp>

namespace cleanpp
{

template<typename Item>
class stack_kernel : public clean_base {
protected:
    template <typename I>
    using _flex_stack_def_t = array_stack<I>;
    static_assert(std::is_base_of<stack_kernel_impl<int>, _flex_stack_def_t<int>>::value,
        "_flex_stack_def_t must derive from stack<Item>");


    std::unique_ptr<stack_kernel_impl<Item>> rep_;
public:

    /**
     * @brief no argument constructor
     *
     * @ensures this = <>
     */
    stack_kernel() : rep_(std::make_unique<_flex_stack_def_t<Item>>()) { }

    template<template<typename> class I>
    stack_kernel(__attribute__((unused)) const I<Item>& impl) : rep_(std::make_unique<I<Item>>()) {
        static_assert(std::is_base_of<stack_kernel_impl<Item>, I<Item>>::value,
            "Template parameter I must derive from stack_kernel<Item>");
    }

    stack_kernel(const stack_kernel<Item>& o) = delete;

    /**
     * @brief Custom move constructor
     *
     * @param o - the stack being moved from
     */
    stack_kernel(stack_kernel<Item>&& o) : rep_(std::move(o.rep_)) {
        o.rep_ = std::make_unique<_flex_stack_def_t<Item>>();
    }

    stack_kernel<Item>& operator=(const stack_kernel<Item>& o) = delete;

    /**
     * @brief custom move assignment operator
     *
     * @param other - the stack being moved from
     * @return the newly-assigned this
     * @ensures this = #other
     */
    stack_kernel<Item>& operator=(stack_kernel<Item>&& other) {
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
     * @param x - the entry to be added
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
    bool operator==(stack_kernel<Item>& other) {
        return *this->rep_ == *other.rep_;
    }

    friend std::ostream& operator<<(std::ostream& out, stack_kernel<Item>& o) {
        return out << *o.rep_;
    }
};

template<typename Item>
class stack : public stack_kernel<Item> {
protected:
    template <typename I>
    using _flex_stack_def_t = array_stack<I>;
    static_assert(std::is_base_of<stack_kernel_impl<int>, _flex_stack_def_t<int>>::value,
        "_flex_stack_def_t must derive from stack<Item>");

public:

    stack() : stack_kernel<Item>() { }

    template<template<typename> class I>
    stack(__attribute__((unused)) const I<Item>& impl) : stack_kernel<Item>(impl) {
        static_assert(std::is_base_of<stack_impl<Item>, I<Item>>::value,
            "Type of impl must derive from stack");
    }

    stack(const stack& other) = delete;

    /*
     clears other
     initialization ensures this = #other
    */
    stack(stack&& other) : stack_kernel<Item>(std::forward<stack_kernel<Item>>(other)) { }

    stack& operator=(const stack& other) = delete;
    /*
     clears other
     replaces this
     ensures this = #other
    */
    stack& operator=(stack&& other) {
        if(&other == this) {
            return *this;
        }
        this->rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_flex_stack_def_t<Item>>();
        return *this;
    }

    /*
     updates this
     ensures this = rev(#this)
    */
    void flip() { 
        std::unique_ptr<stack_impl<Item>> casted_this(static_cast<stack_impl<Item>*>(this->rep_.release()));
        
        casted_this = casted_this->flipped();
        this->rep_ = std::move(casted_this);
        
    }

    stack flipped() {
        std::unique_ptr<stack_impl<Item>> casted_this(static_cast<stack_impl<Item>*>(this->rep_.release()));
        
        casted_this = casted_this->flipped();

        stack flipped_stack;
        flipped_stack.rep_ = std::move(casted_this);
        
        return std::move(flipped_stack);
    }

};

}

#endif /* flexible_stack_h */
