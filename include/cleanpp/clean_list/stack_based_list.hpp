//
//  stack_based_list.hpp
//  Move Semantics
//
//  Created by Alan Weide on 10/19/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef stack_based_list_h
#define stack_based_list_h

#include "clean_list.hpp"

#include "array_stack.hpp"
#include "flexible_stack.hpp"

namespace cleanpp {

template <typename T>
class stack_based_list: public clean_list<T> {
public:
    stack_based_list<T>() {
        prec_ = std::make_unique<array_stack<T>>();
        rem_ = std::make_unique<array_stack<T>>();
    }
    
    stack_based_list<T>(stack_based_list<T> const &other) = delete;
    stack_based_list<T>(stack_based_list<T>&& other) {
        prec_ = std::move(other.prec_);
        rem_ = std::move(other.rem_);
        other.clear(); // done "for free" by previous two statements in this case
    }
    
    stack_based_list<T>& operator=(stack_based_list<T> const &other) = delete;
    stack_based_list<T>& operator=(stack_based_list<T>&& other) {
        if (&other == this) {
            return this;
        }
        prec_ = std::move(other.prec_);
        rem_ = std::move(other.rem_);
        other.clear(); // done "for free" by previous two statements in this case
        return this;
    }
    
    bool operator==(stack_based_list<T> &other) {
        return *(this->prec_) == *(other.prec_) && *(this->rem_) == *(other.rem_);
    }
    
    void clear() override {
        prec_->clear();
        rem_->clear();
    }
    
    void swap(stack_based_list<T>& other) {
        prec_->swap(other.prec_);
        rem_->swap(other.rem_);
    }
    
    void advance() override {
        assert(!is_at_end());
        T x{ };
        x = rem_->pop();
        prec_->push(std::move(x));
    }
    
    void retreat() override {
        assert(!is_at_front());
        T x{ };
        x = prec_->pop();
        rem_->push(std::move(x));
    }
    
    void insert(T&& x) override {
        prec_->push(std::forward<T>(x));
    }
    
    T remove() override {
        assert(!is_at_end());
        return rem_->pop();
    }
    
    bool is_at_end() const override  {
        return rem_->is_empty();
    }
    
    bool is_at_front() const override  {
        return prec_->is_empty();
    }
        
    std::string to_str() override {
        std::stringstream out;
        out << "(";
        std::unique_ptr<clean_stack<T>> rev_prec = std::make_unique<array_stack<T>>();
        while (!prec_->is_empty()) {
            T x;
            x = prec_->pop();
            rev_prec->push(std::move(x));
        }
        out << *rev_prec;
        while (!rev_prec->is_empty()) {
            T x;
            x = rev_prec->pop();
            prec_->push(std::move(x));
        }
        out << ", " << *rem_ << ")";
        return out.str();
    }
private:
    std::unique_ptr<clean_stack<T>> prec_;
    std::unique_ptr<clean_stack<T>> rem_;
};

}

#endif /* ListWithCursor_cpp */
