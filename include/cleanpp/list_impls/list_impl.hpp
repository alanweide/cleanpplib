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
#include "clean_base.hpp"

namespace cleanpp {
template <class T>
class list_kernel_impl: public clean_base {
    /*
     list_kernel is modeled by (prec: string of T,
                                rem:  string of T)
     */
public:
    
    /*
     updates  this
     requires |this.rem| > 0
     ensures  exists A, B, x : #this = (A * <x>, B) : this = (A, <x> * B)
     */
    virtual void advance() = 0;

    /*
     updates   this
     requires |this.prec| > 0
     ensures  exists A, B, x : #this = (A, <x> * B) : this = (A * <x>, B)
     */
    virtual void retreat() = 0;
    
    /*
     updates this
     clears  x
     ensures this = (#this.prec * <x>, #this.rem)
     */
    virtual void insert(T&& x) = 0;

    /*
     updates  this
     ensures  #this = (this.prec * <remove>, this.rem)
     */
    virtual T remove() = 0;
    
    /*
     ensures is_at_end = (|this.rem| = 0)
     */
    virtual bool is_at_end() const = 0;
    
    /*
     ensures is_at_front = (|this.prec| = 0)
     */
    virtual bool is_at_front() const = 0;
        
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
            x = this->remove();
            out << x;
            this->insert(std::move(x));
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
            x = this->remove();
            out << x;
            this->insert(std::move(x));
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
class list_impl: public list_kernel_impl<T> {
public:
    
    /*
     updates this
     ensures this = (<>, #this.prec * #this.rem)
     */
    virtual void reset() {
        while (!this->is_at_front()) {
            this->retreat();
        }
    }
};
}

#endif /* clean_list_h */
