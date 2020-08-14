//
//  clean_queue.hpp
//  Move Semantics
//
//  Created by Alan Weide on 1/15/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#ifndef clean_queue_h
#define clean_queue_h

#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>

namespace cleanpp {
template <typename T>
class queue: public clean_base {
    /*
     queue is modeled by string of T
     */
private:
    virtual std::string to_str() = 0;
public:
    
    /*
     updates this
     clears  x
     ensures this = #this * <x>
     */
    virtual void enqueue(T&& x) = 0;
    
    /*
     updates  this
     requires |this| > 0
     ensures  this * <dequeue> = #this
     */
    virtual T dequeue() = 0;
    
    /*
     ensures is_empty = (|this| = 0)
     */
    virtual bool is_empty() const = 0;
    
    friend std::ostream& operator<<(std::ostream& out, queue<T>& o) {
        return out << o.to_str();
    }
};

        }
        
#endif /* clean_queue_h */
