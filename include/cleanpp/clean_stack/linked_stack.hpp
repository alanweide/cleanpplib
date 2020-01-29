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
#include "clean_stack.hpp"

namespace cleanpp {

template <class T>
class linked_stack: public clean_stack<T> {
private:
    class stack_node: public clean_base {
    private:
    public:
        T contents;
        std::unique_ptr<stack_node> next;
        
        stack_node(): contents(), next() {
        }
        
        stack_node(T& new_contents): contents(std::move(new_contents)), next() {
		}
        
        stack_node(stack_node const &other) = delete;
        stack_node(stack_node&& other): contents(std::move(other.contents)),
        next(std::move(other.next)) {
            other.clear();
        }

        
//        stack_node& operator=(const stack_node& other) = delete;
        stack_node& operator=(stack_node&& other) {
            if (&other == this) {
                return *this;
            }
            contents = std::move(other.contents);
            next = std::move(other.next);
            other.clear();
            return *this;
        }
        
        void clear() override {
			contents = T();
            next.reset();
        }
        
        friend std::ostream& operator<<(std::ostream& out, stack_node& o) {
            return out << o->contents;
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
		if (top_ptr_ != nullptr) {
			top_ptr_.reset();
		}
		assert(top_ptr_ == nullptr);
    }

    
    void push(T& x) override {
        auto new_top = std::make_unique<stack_node>(x);
        new_top->next = std::move(top_ptr_);
        top_ptr_ = std::move(new_top);
    }
    
    void pop(T& x) override {
        x = std::move(top_ptr_->contents);
        top_ptr_ = std::move(top_ptr_->next);
    }
    
    bool is_empty() const override {
        return top_ptr_ == nullptr;
    }
    
    friend std::ostream& operator<<(std::ostream& out, linked_stack<T>& o) {
        out << "<";
        linked_stack<T> temp{};
        while (!o.is_empty())
        {
            T top;
            o.pop(top);
            out << top;
            if (!o.is_empty())
            {
                out << ", ";
            }
            temp.push(top);
        }
        while (!temp.is_empty()) {
            T top;
            temp.pop(top);
            o.push(top);
        }
        out << ">";
        return out;
    }
};

}

#endif /* linked_stack_h */
