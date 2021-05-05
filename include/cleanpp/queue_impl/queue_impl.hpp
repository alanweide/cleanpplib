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
class queue_impl: public clean_base {
    /*
     queue is modeled by string of T
     */
private:
    virtual std::string to_str() = 0;
public:
    
	/**
	 * @brief Adds x to the end of this.
	 * 
	 * @param x - the entry to be added
	 * @ensures this = #this * <x>
	 */
    virtual void enqueue(T&& x) = 0;
    
	/**
	 * @brief Removes and returns the entry at the front of this
	 * 
	 * @return the entry removed
	 * @requires this /= <>
	 * @ensures #this = <dequeue> * this
	 */
    virtual T dequeue() = 0;
    
	/**
	 * @brief Reports whether this is empty
	 * 
	 * @return true iff |this| = 0
	 * @ensures is_empty = (|this| = 0)
	 */
    virtual bool is_empty() const = 0;
    
    friend std::ostream& operator<<(std::ostream& out, queue_impl<T>& o) {
        return out << o.to_str();
    }
};

        }
        
#endif /* clean_queue_h */
