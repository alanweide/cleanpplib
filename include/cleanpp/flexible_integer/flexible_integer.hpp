//
//  flexible_integer.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/13/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef flexible_integer_h
#define flexible_integer_h

#include <clean_integer/big_integer.hpp>
#include <clean_integer/nn_integer.hpp>

namespace cleanpp {

typedef nn_integer _flex_int_def_t;

class flex_big_integer_kernel: public clean_base {
protected:
	std::unique_ptr<big_integer_kernel> rep_;
public:
	/*
	 big_integer_kernel is modeled by integer
	 */
	// The "base" of the number
	static const int RADIX = 10;
	
    flex_big_integer_kernel(long n = 0) {
        rep_ = std::make_unique<_flex_int_def_t>(n);
    }

    template<typename I>
    flex_big_integer_kernel(__attribute__((unused)) const I& impl, long n = 0) {
		static_assert(std::is_base_of<big_integer_kernel, I>::value,
                      "Type of impl must derive from big_integer_kernel");
        rep_ = std::make_unique<I>(n);
	}
	
	flex_big_integer_kernel(const flex_big_integer_kernel &other) = delete;
    flex_big_integer_kernel(flex_big_integer_kernel&& other) : rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<_flex_int_def_t>();
	}
	
	flex_big_integer_kernel& operator=(const flex_big_integer_kernel& other) = delete;
	flex_big_integer_kernel& operator=(flex_big_integer_kernel&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<_flex_int_def_t>();
		return *this;
	}
	
	void clear() override {
		this->rep_->clear();
	}
	
	/*
	 updates  this
	 requires 0 <= d and d < 10
	 ensures  |this| = |#this| * RADIX + d and
	 this < 0 iff #this < 0
	 */
	void multiply_by_radix(int d) {
		rep_->multiply_by_radix(d);
	}
	
	/*
	 updates  this
	 replaces d
	 ensures  |#this| = |this| * RADIX + d and
	 0 <= d and d < 10 and
	 this < 0 iff #this < 0
	 */
	int divide_by_radix() {
		return rep_->divide_by_radix();
	}
	
	/*
	 updates this
	 ensures this = -#this
	 */
	void negate() {
		rep_->negate();
	}
	
	/*
	 ensures  this < 0 ==> sign = NEGATIVE and
	 this = 0 ==> sign = ZERO and
	 this > 0 ==> sign = POSITIVE
	 */
	integer_sign sign() const {
		return rep_->sign();
	}
	
	/*
	 ensures `==` = (this = other)
	 */
	bool operator==(flex_big_integer_kernel &other) {
		return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, flex_big_integer_kernel& o) {
		return out << *o.rep_;
	}
};

class flex_big_integer: public flex_big_integer_kernel {
public:
    flex_big_integer(long n = 0): flex_big_integer_kernel(n) {}

    template<typename I>
    flex_big_integer(__attribute__((unused)) const I& impl, long n = 0): flex_big_integer_kernel(impl, n) {
		static_assert(std::is_base_of<big_integer, I>::value,
					  "Type of impl must derive from big_integer");
	}
	
	flex_big_integer(const flex_big_integer& other) = delete;
    flex_big_integer(flex_big_integer&& other): flex_big_integer_kernel(std::forward<flex_big_integer_kernel>(other)) {
	}
	
	flex_big_integer& operator=(const flex_big_integer& other) = delete;
	flex_big_integer& operator=(flex_big_integer&& other) {
		if (&other == this) {
			return *this;
		}
		this->rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_flex_int_def_t>();
		return *this;
	}
	
	/*
	 updates this
	 ensures this = #this + 1
	 */
	void increment() {
		std::unique_ptr<big_integer> casted(static_cast<big_integer*>(this->rep_.release()));
		
        casted->increment();
		
        this->rep_ = std::move(casted);
	}
	
	/*
	 updates this
	 ensures this = #this - 1
	 */
	void decrement() {
		std::unique_ptr<big_integer> casted(static_cast<big_integer*>(this->rep_.release()));
		
        casted->decrement();
		
        this->rep_ = std::move(casted);
	}
	
	/*
	 replaces this
	 ensures  this = n
	 */
	void set_from_long(long n) {
		std::unique_ptr<big_integer> casted(static_cast<big_integer*>(this->rep_.release()));
        
		casted->set_from_long(n);
		
        this->rep_ = std::move(casted);
	}
	
	/*
	 requires 0 <= d and d < 10
	 ensures  this = |#this| and abs = [POSITIVE, ZERO, or NEGATIVE as this > 0, = 0, or < 0]
	 */
	integer_sign abs() {
		std::unique_ptr<big_integer> casted(static_cast<big_integer*>(this->rep_.release()));
        
		integer_sign sign = casted->abs();
		
        this->rep_ = std::move(casted);
		return sign;
	}
	
	/*
	 updates  this
	 ensures  assign_sign = NEGATIVE ==> this = -|#this| and
              assign_sign = ZERO     ==> this = #this and
              assign_sign = POSITIVE ==> this = |#this|
	 */
	void assign_sign(integer_sign sign){
		std::unique_ptr<big_integer> casted(static_cast<big_integer*>(this->rep_.release()));
        
		casted->assign_sign(sign);
		
        this->rep_ = std::move(casted);
	}
	
	/*
	 ensures clone = this
	 */
	flex_big_integer clone() {
        flex_big_integer clone(_flex_int_def_t{});
		std::unique_ptr<big_integer> casted(static_cast<big_integer*>(this->rep_.release()));
        
		clone.rep_ = casted->clone();
		
        this->rep_ = std::move(casted);
		return clone;
	}
	
	/*
	 ensures  add = #x + y
	 */
	friend flex_big_integer add(flex_big_integer&& x, flex_big_integer &y) {
        flex_big_integer sum(std::forward<flex_big_integer>(x));
		
		std::unique_ptr<big_integer> sum_casted(static_cast<big_integer*>(sum.rep_.release()));
		std::unique_ptr<big_integer> y_casted(static_cast<big_integer*>(y.rep_.release()));
        
		sum_casted = add(std::move(sum_casted), y_casted);
		
        y.rep_ = std::move(y_casted);
		sum.rep_ = std::move(sum_casted);

		return sum;
	}
	
	/*
	 ensures subtract = #x - y
	 */
    friend flex_big_integer subtract(flex_big_integer&& x, flex_big_integer &y) {
        flex_big_integer diff(std::forward<flex_big_integer>(x));
        
        std::unique_ptr<big_integer> diff_casted(static_cast<big_integer*>(diff.rep_.release()));
        std::unique_ptr<big_integer> y_casted(static_cast<big_integer*>(y.rep_.release()));
        
        diff_casted = subtract(std::move(diff_casted), y_casted);
        
        y.rep_ = std::move(y_casted);
        diff.rep_ = std::move(diff_casted);

		return diff;
	}
	
	/*
	 ensures compare > 0 ==> x > y and
	 compare = 0 ==> x = y and
	 compare < 0 ==> x < y
	 */
    friend int compare(flex_big_integer& x, flex_big_integer &y) {
        int comp;

		std::unique_ptr<big_integer> x_casted(static_cast<big_integer*>(x.rep_.release()));
		std::unique_ptr<big_integer> y_casted(static_cast<big_integer*>(y.rep_.release()));
        
		comp = compare(x_casted, y_casted);
		
        y.rep_ = std::move(y_casted);
		x.rep_ = std::move(x_casted);
		
		return comp;
	}
		
};

}

#endif /* flexible_integer_h */
