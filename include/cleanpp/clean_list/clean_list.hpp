//
//  clean_list.hpp
//  Move Semantics
//
//  Created by Alan Weide on 12/6/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef clean_list_h
#define clean_list_h

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <clean_base.hpp>

namespace cleanpp {
template <class T>
class list_kernel: public clean_base {
public:
    virtual void advance() = 0;
    virtual void retreat() = 0;
    virtual void insert(T& x) = 0;
    virtual void remove(T& x) = 0;
    virtual bool is_at_end() = 0;
    virtual bool is_at_front() = 0;
        
    virtual std::string to_str() {
        std::stringstream out;
        
        // Reset this and count position
        int pos = 0;
        while (!this->is_at_front()) {
            this->retreat();
            pos++;
        }
        
        // Append first part of this to out
        out << "(<";
        while (!this->is_at_end() && pos > 0) {
            T x;
            this->remove(x);
            out << x;
            this->insert(x);
            pos--;
            if (pos != 0) {
                out << ", ";
            }
        }
        out << ">, ";
        
        // Append second part of this to out
        out << "<";
        while (!this->is_at_end()) {
            T x;
            this->remove(x);
            out << x;
            this->insert(x);
            pos++;
            if (!this->is_at_end()) {
                out << ", ";
            }
        }
        out << ">)";
        
        // Reset this this to original position
        while (pos > 0) {
            this->retreat();
            pos--;
        }
        
        return out.str();
    }
};

template<class T>
class list: public list_kernel<T> {
public:
    virtual void reset() {
        while (!this->is_at_front()) {
            this->retreat();
        }
    }
};
}

#endif /* clean_list_h */
