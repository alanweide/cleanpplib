//
//  template_list.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/14/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef template_list_h
#define template_list_h

#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <sstream>
#include "clean_base.hpp"
#include "clean_list.hpp"

namespace cleanpp {

template<template<typename> class I, typename Item>
class t_list;

template <template<typename> class I, typename Item>
class t_list_kernel: public clean_base {
private:
	std::unique_ptr<clean_list_kernel<Item>> rep_;
	/*
	 list_kernel is modeled by (prec: string of T,
	 rem:  string of T)
	 */
public:
	
	t_list_kernel() {
		rep_ = std::make_unique<I<Item>>();
	}
	
	t_list_kernel(const t_list_kernel<I, Item>& other) = delete;
	t_list_kernel(t_list_kernel<I, Item>&& other): rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<I<Item>>();
	}
	
	t_list_kernel& operator=(const t_list_kernel<I, Item>& other) = delete;
    
//    template<template<typename> class I2>
//	t_list_kernel<I2, Item>& operator=(t_list_kernel<I2, Item>&& other) {
    t_list_kernel& operator=(t_list_kernel<I, Item>&& other) {
    if (&other == this) {
			return this;
		}
		rep_ = std::move(other.rep_);
//		other.rep_ = std::make_unique<I2<Item>>();
        other.rep_ = std::make_unique<I<Item>>();
		return this;
	}
	
	void clear() override {
		this->rep_->clear();
	}
	
	/*
	 updates  this
	 requires |this.rem| > 0
	 ensures  exists A, B, x : #this = (A * <x>, B) : this = (A, <x> * B)
	 */
	void advance() {
		this->rep_->advance();
	}
	
	/*
	 updates   this
	 requires |this.prec| > 0
	 ensures  exists A, B, x : #this = (A, <x> * B) : this = (A * <x>, B)
	 */
	void retreat() {
		this->rep_->retreat();
	}
	
	/*
	 updates this
	 clears  x
	 ensures this = (#this.prec * <x>, #this.rem)
	 */
	void insert(Item&& x) {
		this->rep_->insert(std::forward<Item>(x));
	}
	
	/*
	 updates  this
	 ensures  #this = (this.prec * <remove>, this.rem)
	 */
	Item remove() {
		return this->rep_->remove();
	}
	
	/*
	 ensures is_at_end = (|this.rem| = 0)
	 */
	bool is_at_end() const {
		return this->rep_->is_at_end();
	}
	
	/*
	 ensures is_at_front = (|this.prec| = 0)
	 */
	bool is_at_front() const {
		return this->rep_->is_at_front();
	}
	
	std::string to_str() {
		return this->rep_->to_str();
	}
	
	bool operator==(t_list_kernel<I, Item> &other) {
		return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, t_list_kernel<I, Item>& o) {
		return out << *o.rep_;
	}
	
	friend class t_list<I, Item>;
};

template<template<typename> class I, typename Item>
class t_list: public t_list_kernel<I, Item> {
public:
	
	/*
	 updates this
	 ensures this = (<>, #this.prec * #this.rem)
	 */
	void reset() {
		std::unique_ptr<clean_list<Item>> casted(static_cast<clean_list<Item>*>(this->rep_.release()));
		
        casted->reset();
		
        this->rep_ = std::move(casted);
	}
};
}


#endif /* template_list_h */
