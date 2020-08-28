//
//  flexible_list.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/14/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef flexible_list_h
#define flexible_list_h

#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <sstream>
#include <clean_base.hpp>
#include <clean_list/clean_list.hpp>
#include <clean_list/stack_based_list.hpp>

namespace cleanpp {

template <typename I>
using _flex_list_def_t = stack_based_list<I>;

template<typename Item>
class flex_list_kernel: public clean_base {
protected:
	std::unique_ptr<list_kernel<Item>> rep_;
	/*
	 list_kernel is modeled by (prec: string of T,
	 rem:  string of T)
	 */
public:
	
	flex_list_kernel(): rep_(std::make_unique<_flex_list_def_t<Item>>()) {
	}
	
	template <template<typename> class I>
	flex_list_kernel(__attribute__((unused)) const I<Item>& impl): rep_(std::make_unique<I<Item>>()) {
		static_assert(std::is_base_of<list_kernel<Item>, I<Item>>::value,
					  "Template parameter I must derive from list_kernel<Item>");
	}
	
	flex_list_kernel(const flex_list_kernel<Item>& other) = delete;
	flex_list_kernel(flex_list_kernel<Item>&& other): rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<_flex_list_def_t<Item>>();
	}
	
	flex_list_kernel<Item>& operator=(const flex_list_kernel<Item>& other) = delete;
    flex_list_kernel<Item>& operator=(flex_list_kernel<Item>&& other) {
    if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_flex_list_def_t<Item>>();
		return *this;
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
	
	bool operator==(flex_list_kernel<Item> &other) {
		return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, flex_list_kernel<Item>& o) {
		return out << *o.rep_;
	}
};

template<typename Item>
class flex_list: public flex_list_kernel<Item> {
public:
	template <template<typename> class I>
	flex_list(__attribute__((unused)) const I<Item>& impl): flex_list_kernel<Item>(impl) {
		static_assert(std::is_base_of<list<Item>, I<Item>>::value,
					  "Template parameter I must derive from list<Item>");
	}
	
	/*
	 updates this
	 ensures this = (<>, #this.prec * #this.rem)
	 */
	void reset() {
		std::unique_ptr<list<Item>> casted(static_cast<list<Item>*>(this->rep_.release()));
		
        casted->reset();
		
        this->rep_ = std::move(casted);
	}
};
}


#endif /* flexible_list_h */
