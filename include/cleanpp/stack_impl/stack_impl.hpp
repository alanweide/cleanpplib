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
#include <stack_impl/linked_stack.hpp>



namespace cleanpp
{

template<class T>
class linked_stack;

template <class T>
class stack_kernel_impl : public clean_base {
    /*
     stack is modeled by string of T
     */
private:
    virtual std::string to_str() = 0;
public:

    /**
     * @brief Adds x to the top of this
     *
     * @param x - the entry to be aded
     * @ensures this = <x> * #this
     */
    virtual void push(T&& x) = 0;

    /**
     * @brief Removes x from the top of this
     *
     * @return the entry rmemoved
     * @requires this /= <>
     * @ensures #this = <pop> * this
     */
    virtual T pop() = 0;

    /**
     * @brief Reports whether this is empty
     *
     * @return true iff |this| = 0
     * @ensures is_empty = (|this| = 0)
     */
    virtual bool is_empty() const = 0;

    /**
     * @brief overloaded equality operator
     *
     * @param other - stack to compare with
     * @return true iff this = other
     * @ensures '==' = (this = other)
     */
    bool operator==(stack_kernel_impl<T>& other) {
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

    friend std::ostream& operator<<(std::ostream& out, stack_kernel_impl<T>& o) {
        return out << o.to_str();
    }
};

template<class T>
class stack_impl : public stack_kernel_impl<T> {
private:
    /***** helper method *****/
    void move_to_bottom(T&& element) {
        if (!this->is_empty()) {
            T top = this->pop();
            this->move_to_bottom(std::move(element));
            this->push(std::move(top));
        } else {
            this->push(std::move(element));
        }
    }

public:
    /*
     updates this
     ensures this = rev(#this)
    */
    //   void flip() {
    //       if(!this->is_empty()){
    //           T top = this->pop();
    //           this->flip();
    //           this->move_to_bottom(std::move(top));
    //       }
    //   }

    virtual std::unique_ptr<stack_impl<T>> new_instance() = 0;

    virtual std::unique_ptr<stack_impl<T>> flipped() {
        std::unique_ptr<stack_impl<T>> temp = this->new_instance();
        while (!this->is_empty()) {
            T popped = this->pop();
            temp->push(std::move(popped));
        }
        return temp;
    }

    virtual void flip() {
        std::unique_ptr<stack_impl<T>> temp = this->new_instance();
        // *temp = std::move(*this);
        // stack_impl<T>* temp = std::move(this);
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << "::this = " << *this << std::endl;
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << "::temp = " << *temp << std::endl;
        while (!this->is_empty()) {
            T popped = this->pop();
            std::cout << __FILE__ << ":" << __LINE__ << __func__ << "::popped = " << popped << std::endl;
            temp->push(std::move(popped));
        }
        *this = *temp; //problem code
        std::cout << __FILE__ << ":" << __LINE__ << __func__ << "::this = " << *this << std::endl;
        std::cout << __FILE__ << ":" << __LINE__ << __func__ << "::temp = " << *temp << std::endl;
    }
};

}

#endif /* clean_stack_h */
