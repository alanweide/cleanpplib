//
//  template_queue.hpp
//  Move Semantics
//
//  Created by Alan Weide on 8/6/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef template_queue_h
#define template_queue_h

#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>
#include <clean_queue/clean_queue.hpp>

namespace cleanpp {

template <template<typename> class I, typename Item>
class t_queue: public clean_base {
    /*
     queue is modeled by string of T
     */
private:
    std::unique_ptr<queue<Item>> rep_;
public:
    
    t_queue() {
        rep_ = std::make_unique<I<Item>>();
    }
    
    t_queue(const t_queue<I, Item> &o) = delete;
    t_queue(t_queue<I, Item>&& o): rep_(std::move(o.rep_)) {
        o.rep_ = std::make_unique<I<Item>>();
    }
    
    t_queue<I, Item>& operator=(const t_queue<I, Item>& o) = delete;
    t_queue<I, Item>& operator=(t_queue<I, Item>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<I<Item>>();
		return *this;
    }
    
    void clear() {
		this->rep_->clear();
    }

    /*
     updates this
     clears  x
     ensures this = #this * <x>
     */
    void enqueue(Item&& x) {
        rep_->enqueue(std::forward<Item>(x));
    }
    
    /*
     updates  this
     replaces x
     requires |this| > 0
     ensures  this * <x> = #this
     */
	Item dequeue() {
        return rep_->dequeue();
    }
    
    /*
     ensures is_empty = (|this| = 0)
     */
	bool is_empty() const {
        return rep_->is_empty();
    }
    
    friend std::ostream& operator<<(std::ostream& out, t_queue<I, Item>& o) {
        return out << *o.rep_;
    }
};

        }
        
#endif /* template_queue_h */
