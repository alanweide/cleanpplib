//
//  array_stack.hpp
//  Move Semantics
//
//  Created by Alan Weide on 9/25/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef array_stack_h
#define array_stack_h

#include <stdio.h>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>

#include "clean_stack.hpp"

namespace cleanpp {

template <typename T>
class array_stack: public clean_stack<T>
{
private:
    static const int START_CAP = 6;
    int cap_;
    
    int length_;
    int init_so_far_;
    std::unique_ptr<T[]> contents_;
    
    std::string to_str() override {
        std::stringstream out;
        out << "<";
        int i = length_;
        while (i > 0)
        {
            i--;
            out << contents_[i];
            if (i > 0)
            {
                out << ", ";
            }
        }
        out << ">";
        return out.str();
    }
    
    void resize_if_needed() {
        int old_cap = cap_;
        if (length_ == cap_) {
            cap_ *= 2;
        } else if (length_ * 2 < cap_) {
            cap_ /= 2;
        }
        if (cap_ != old_cap) {
            auto temp_cont = std::move(contents_);
            contents_ = std::make_unique<T[]>(cap_);
            for (int i = 0; i < length_; i++) {
                contents_[i] = std::move(temp_cont[i]);
            }
        }
    }
public:
    
    array_stack<T>():
    cap_(START_CAP), length_(0), init_so_far_(0)
    {
        contents_ = std::make_unique<T[]>(cap_);
        //            for (int i = 0; i < cap; i++) {
        //                contents_[i] = std::make_unique<T>();
        //            }
    }
    
    array_stack<T>(array_stack<T> const &other) = delete;
    array_stack<T>(array_stack<T>&& other):
    cap_(std::move(other.cap_)), length_(std::move(other.length_)), init_so_far_(std::move(other.init_so_far_)), contents_(std::move(other.contents_))
    {
        other.clear();
    }
    
    array_stack<T>& operator=(const array_stack<T>& other) = delete;
    array_stack<T>& operator=(array_stack<T>&& other) {
        if (&other == this) {
            return *this;
        }
        
        cap_ = std::move(other.cap_);
        length_ = std::move(other.length_);
        init_so_far_ = std::move(other.init_so_far_);
        contents_ = std::move(other.contents_);
        other.clear();
        return *this;
    }

    ~array_stack() {
    }
    
    void clear() override {
        length_ = 0;
    }
        
    void push(T& x) override {
        contents_[length_] = std::move(x);
        length_++;
        
        resize_if_needed();
    }
    
    void pop(T& x) override {
        //		std::cout << "\nBoundedMovingStack_Hidden::pop(T& x):\n";
        
        length_--;
        x = std::move(contents_[length_]);
        
        resize_if_needed();
    }
    
    bool is_empty() const override {
        return length_ == 0;
    }
    
};

}

#endif /* array_stack_h */
