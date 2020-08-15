//
//  template_nn.hpp
//  Cleanpp
//
//  Created by Alan Weide on 7/23/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef template_nn_hpp
#define template_nn_hpp

#include <stdio.h>
#include <clean_base.hpp>
#include <clean_nn/natural_number.hpp>

namespace cleanpp {

template<class I>
class t_natural_number;

template <class I>
class t_natural_number_kernel: public clean_base {
private:
	std::unique_ptr<natural_number_kernel> rep_;
public:
	/*
	 type NATURAL is integer
	 exemplar   n
	 constraint n >= 0
	 
	 natural_number_kernel is modeled by NATURAL
	 */
	static const int RADIX = 10;
	
	t_natural_number_kernel(long n = 0) {
		rep_ = std::make_unique<I>(n);
	}
	
	t_natural_number_kernel(const t_natural_number_kernel<I>& other) = delete;
	t_natural_number_kernel(t_natural_number_kernel<I>&& other): rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<I>();
	}
	
	t_natural_number_kernel<I>& operator=(const t_natural_number_kernel<I>& other) = delete;
	t_natural_number_kernel<I>& operator=(t_natural_number_kernel<I>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<I>();
		return *this;
	}
	
	void clear() override{
		this->rep_->clear();
	}
	
	/*
	 ensures is_zero = (this = 0)
	 */
	bool is_zero() const{
		return this->rep_->is_zero();
	}
	
	/*
	 updates  this
	 requires 0 <= d and d < RADIX
	 ensures  this = #this * RADIX + d
	 */
	void multiply_by_radix(int&& d){
		this->rep_->multiply_by_radix(d);
	}
	
	/*
	 updates  this
	 ensures  #this = this * RADIX + d and
	 0 <= d and d < RADIX
	 */
	int&& divide_by_radix() {
		return this->rep_->divide_by_radix();
	}
	
	/*
	 ensures `==` = (this = other)
	 */
	template<class I2>
	bool operator==(t_natural_number_kernel<I2> &other)	{
		return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, t_natural_number_kernel<I>& o) {
		return out << *(o.rep_);
	}
	
	friend class t_natural_number<I>;
};

template<class I>
class t_natural_number: public t_natural_number_kernel<I> {
private:
	//	std::unique_ptr<natural_number_secondary> rep_;
public:
	
	t_natural_number(long n = 0): t_natural_number_kernel<I>(n) {
		static_assert(std::is_base_of<natural_number_secondary, I>::value, "Template parameter I must derive from natural_number_secondary");
	}
	
	t_natural_number(const t_natural_number<I>& other) = delete;
	t_natural_number(t_natural_number<I>&& other): t_natural_number_kernel<I>(std::move(other)) {
		static_assert(std::is_base_of<natural_number_secondary, I>::value, "Template parameter I must derive from natural_number_secondary");
		other.rep_ = std::make_unique<I>();
	}
	
	t_natural_number<I>& operator=(const t_natural_number<I>& other) = delete;
	t_natural_number<I>& operator=(t_natural_number<I>&& other) {
		if (&other == this) {
			return *this;
		}
		this->rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<I>();
		return *this;
	}
	
	/*
	 updates this
	 ensures this = #this + 1
	 */
	void increment() {
		std::unique_ptr<natural_number_secondary> casted(dynamic_cast<natural_number_secondary*>(this->rep_.release()));
		casted->increment();
		this->rep_ = std::move(casted);
	}
	
	/*
	 updates  this
	 requires this > 0
	 ensures  this = #this - 1
	 */
	void decrement() {
		assert(!this->is_zero());
		std::unique_ptr<natural_number_secondary> casted(dynamic_cast<natural_number_secondary*>(this->rep_.release()));
		casted->decrement();
		this->rep_ = std::move(casted);
	}
	
	/*
	 replaces this
	 requires n >= 0
	 ensures  this = n
	 */
	void set_from_long(long n) {
		assert(n >= 0);
		std::unique_ptr<natural_number_secondary> casted(dynamic_cast<natural_number_secondary*>(this->rep_.release()));
		casted->set_from_long(n);
		this->rep_ = std::move(casted);
	}
	
	/*
	 ensures add = #x + y
	 */
	template<class I2>
	friend t_natural_number<I> add(t_natural_number<I>&& x, t_natural_number<I2> &y) {
		int x_low = x.divide_by_radix();
		int y_low = y.divide_by_radix();
		if (!y.is_zero()) {
			x = add(std::move(x), y);
		}
		x_low += y_low;
		if (x_low >= t_natural_number_kernel<I>::RADIX) {
			x_low -= t_natural_number_kernel<I>::RADIX;
			x.increment();
		}
		x.multiply_by_radix(std::move(x_low));
		y.multiply_by_radix(std::move(y_low));
		return std::move(x);
	}
	
	/*
	 requires x >= y
	 ensures  add = #x - y
	 */
	template<class I2>
	friend t_natural_number<I> subtract(t_natural_number<I>&& x, t_natural_number<I2> &y) {
		int x_low;
		x_low = x.divide_by_radix();
		int y_low;
		y_low = y.divide_by_radix();
		if (!y.is_zero()) {
			x = subtract(std::move(x), y);
		}
		x_low -= y_low;
		if (x_low < 0) {
			x_low += t_natural_number_kernel<I>::RADIX;
			x.decrement();
		}
		x.multiply_by_radix(std::move(x_low));
		y.multiply_by_radix(std::move(y_low));
		return std::move(x);
	}
};

}

#endif /* template_nn_hpp */
