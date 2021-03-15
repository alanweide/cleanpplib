//
//  template_queue.hpp
//  Move Semantics
//
//  Created by Alan Weide on 8/6/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef flexible_queue_h
#define flexible_queue_h

#include <stdio.h>
#include <iostream>
#include <memory>

#include "clean_base.hpp"
#include "queue_impl.hpp"
#include "array_queue.hpp"
#include "linked_queue.hpp"

namespace cleanpp {

template <typename I>
using _queue_def_t = array_queue<I>;

template <typename Item>
class queue: public clean_base {
	/*
	 queue is modeled by string of Item
	 */
protected:
	std::unique_ptr<queue_impl<Item>> rep_;
public:

	/*
	 ensures this = <>
	 */
	queue(): rep_(std::make_unique<_queue_def_t<Item>>()) {
	}

	template<template<typename> class I>
	queue(__attribute__((unused)) const I<Item>& impl): rep_(std::make_unique<I<Item>>()) {
		static_assert(std::is_base_of<queue_impl<Item>, I<Item>>::value,
					  "Template parameter I must derive from cleanpp::queue");
	}

	queue(const queue<Item> &o) = delete;
	/*
	 clears  other
	 ensures this = #other
	 */
	queue(queue<Item>&& other): rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<_queue_def_t<Item>>();
	}

	queue<Item>& operator=(const queue<Item>& other) = delete;
	/*
	 clears  other
	 ensures this = #other
	 */
	queue<Item>& operator=(queue<Item>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<_queue_def_t<Item>>();
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

    /*
     ensures `==` = (this = other)
     */
    bool operator==(queue<Item>& other) {
        return *this->rep_ == *other.rep_;
    }

    friend std::ostream& operator<<(std::ostream& out, queue<Item>& o) {
		return out << *o.rep_;
	}
};

}

#endif /* flexible_queue_h */
