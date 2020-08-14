//
//  linked_stack.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef linked_stack_h
#define linked_stack_h

#include <type_traits>
#include <stdio.h>
#include <sstream>
#include "clean_stack.hpp"

namespace cleanpp {

template <class T>
class linked_stack: public stack<T> {
private:
    class stack_node: public clean_base {
    private:
//        T contents_;
        std::unique_ptr<T> contents_;
        std::unique_ptr<stack_node> next_;
    public:
        stack_node() {
            contents_ = std::make_unique<T>();
            next_ = nullptr;
        }
        
        stack_node(T&& new_contents, std::unique_ptr<stack_node>&& new_next):
//            contents_(std::move(new_contents)),
            next_(std::forward<std::unique_ptr<stack_node>>(new_next)) {
                contents_ = std::make_unique<T>(std::forward<T>(new_contents));
		}
        
        stack_node(stack_node const &other) = delete;
        stack_node(stack_node&& other):
            contents_(std::move(other.contents_)),
            next_(std::move(other.next_)) {

            other.clear();
        }

        
        stack_node& operator=(const stack_node& other) = delete;
        stack_node& operator=(stack_node&& other) {
            if (&other == this) {
                return *this;
            }
            contents_ = std::move(other.contents_);
            next_ = std::move(other.next_);
            other.clear();
            return *this;
        }
        
        T contents() {
            // return std::move(contents_);
            return std::move(*contents_);
        }
                
        std::unique_ptr<stack_node>&& next() {
            return std::move(next_);
        }
        
        void clear() override {
            contents_ = std::make_unique<T>();
            next_.reset();
        }
                
        virtual ~stack_node() = default;
    };
    
    std::unique_ptr<stack_node> top_ptr_;
public:
    linked_stack<T>() {
        top_ptr_ = nullptr;
    }
    
    linked_stack<T>(linked_stack<T> const &other) = delete;
    linked_stack<T>(linked_stack<T>&& other):
    top_ptr_(std::move(other.top_ptr_)) {
        other.clear();
    }
    
    linked_stack<T>& operator=(const linked_stack<T>& other) = delete;
    linked_stack<T>& operator=(linked_stack<T>&& other) {
        if (&other == this) {
            return *this;
        }
        
        top_ptr_ = std::move(other.top_ptr_);
        other.clear();
        return *this;
    }
    
    void clear() override {
		if (!is_empty()) {
			top_ptr_.reset();
		}
		assert(is_empty());
    }

    
    void push(T&& x) override {
        top_ptr_ = std::make_unique<stack_node>(std::forward<T>(x), std::move(top_ptr_));
    }
    
    T pop() override {
        assert(!is_empty());
		T pop = top_ptr_->contents();
        top_ptr_ = top_ptr_->next();
		return std::move(pop);
    }
    
    bool is_empty() const override {
        return top_ptr_ == nullptr;
    }
    
private:
    std::string to_str() override {
        std::stringstream out;
        out << "<";
        linked_stack<T> temp{};
        while (!this->is_empty())
        {
            T top;
            top = this->pop();
            out << top;
            if (!is_empty())
            {
                out << ", ";
            }
            temp.push(std::move(top));
        }
        while (!temp.is_empty()) {
            T top;
            top = temp.pop();
            this->push(std::move(top));
        }
        out << ">";
        return out.str();
    }
};

}

#endif /* linked_stack_h */
