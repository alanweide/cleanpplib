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

#include <clean_base.hpp>
#include <queue_impl/queue_impl.hpp>
#include <queue_impl/array_queue.hpp>

namespace cleanpp
{

template <typename I>
using _queue_def_t = array_queue<I>;

template <typename Item>
class queue_kernel : public clean_base {
	/**
	 queue is modeled by string of Item
	 */
protected:
	std::unique_ptr<queue_kernel_impl<Item>> rep_;
	
public:

	/**
	 * @brief no argument constructor
	 *
	 * @ensures this = <>
	 */
	queue_kernel() : rep_(std::make_unique<_queue_def_t<Item>>()) { }

	template<template<typename> class I>
	queue_kernel(__attribute__((unused)) const I<Item>& impl) : rep_(std::make_unique<I<Item>>()) {
		static_assert(std::is_base_of<queue_impl<Item>, I<Item>>::value,
			"Template parameter I must derive from queue_kernel");
	}

	queue_kernel(const queue_kernel<Item>& o) = delete;


	/**
	 * @brief Custom move constructor
	 *
	 * @param other - the queue being moved from
	 */
	queue_kernel(queue_kernel<Item>&& other) : rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<_queue_def_t<Item>>();
	}

	queue_kernel<Item>& operator=(const queue_kernel<Item>& other) = delete;

	/**
	  * @brief custom move assignment operator
	  *
	  * @param other - the queue being moved from
	  * @return the newly-assigned this
	  * @ensures this = #other
	  */
	queue_kernel<Item>& operator=(queue_kernel<Item>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<_queue_def_t<Item>>();
		return *this;
	}

	/**
	 * @brief clears this
	 */
	void clear() {
		this->rep_->clear();
	}

	/**
	 * @brief Adds x to the end of this.
	 *
	 * @param x - the entry to be added
	 * @ensures this = #this * <x>
	 */
	void enqueue(Item&& x) {
		rep_->enqueue(std::forward<Item>(x));
	}

	/**
	 * @brief Removes and returns the entry at the front of this
	 *
	 * @return the entry removed
	 * @requires this /= <>
	 * @ensures #this = <dequeue> * this
	 */
	Item dequeue() {
		return rep_->dequeue();
	}

	/**
	 * @brief Reports whether this is empty
	 *
	 * @return true iff |this| = 0
	 * @ensures is_empty = (|this| = 0)
	 */
	bool is_empty() const {
		return rep_->is_empty();
	}


	/**
	 * @brief overloaded equality operator
	 *
	 * @param other
	 * @return true iff (this = other)
	 * @ensures '==' = (this = other)
	 */
	bool operator==(queue_kernel<Item>& other) {
		return *this->rep_ == *other.rep_;
	}

	friend std::ostream& operator<<(std::ostream& out, queue_kernel<Item>& o) {
		return out << *o.rep_;
	}
};

template<typename Item>
class queue : public queue_kernel<Item> {
public:

	queue() : queue_kernel<Item>() { }

	template<template<typename> class I>
	queue(__attribute__((unused)) const I<Item>& impl) : queue_kernel<Item>(impl) {
		static_assert(std::is_base_of<queue_impl<Item>, I<Item>>::value,
			"Type of impl must derive from queue");
	}

	queue(const queue& other) = delete;
	/*
	 clears other
	 initialization ensures this = #other
	*/
	queue(queue&& other) : queue_kernel<Item>(std::forward<queue_kernel<Item>>(other)) { }

	queue& operator=(const queue& other) = delete;
	/*
	 clears other
	 replaces this
	 ensures this = #other
	*/
	queue& operator=(queue&& other) {
		if (&other == this) {
			return *this;
		}
		this->rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<_queue_def_t<Item>>();
		return *this;
	}

	/*
	 updates this
	 clears q
	 ensures this = #this * #q
	*/
	void append(queue&& q){
		std::unique_ptr<queue_impl<Item>> casted_this(static_cast<queue_impl<Item>*>(this->rep_.release()));
		std::unique_ptr<queue_impl<Item>> casted_q(static_cast<queue_impl<Item>*>(q.rep_.release()));
		
		casted_this->append(std::move(casted_q));

		this->rep_ = std::move(casted_this);
		q.rep_ = std::make_unique<_queue_def_t<Item>>();
		
	}

};

}

#endif /* flexible_queue_h */
