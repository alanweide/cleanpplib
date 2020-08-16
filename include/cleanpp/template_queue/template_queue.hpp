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
	 queue is modeled by string of Item
	 */
private:
	std::unique_ptr<queue<Item>> rep_;
public:
	
	/*
	 ensures this = <>
	 */
	t_queue() {
		rep_ = std::make_unique<I<Item>>();
	}
	
	t_queue(const t_queue<I, Item> &o) = delete;
	/*
	 clears  other
	 ensures this = #other
	 */
	t_queue(t_queue<I, Item>&& other): rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<I<Item>>();
	}
	
	t_queue<I, Item>& operator=(const t_queue<I, Item>& other) = delete;
	/*
	 clears  other
	 ensures this = #other
	 */
	t_queue<I, Item>& operator=(t_queue<I, Item>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<I<Item>>();
		return *this;
	}
	
	/*
	 clears this
	 */
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
	 requires |this| > 0
	 ensures  this * <dequeue> = #this
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
