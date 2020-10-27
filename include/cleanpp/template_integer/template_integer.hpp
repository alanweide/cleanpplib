//
//  template_integer.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/13/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef template_integer_h
#define template_integer_h

#include "clean_integer.hpp"

namespace cleanpp {

template<typename I>
class t_integer_kernel: public clean_base {
protected:
	std::unique_ptr<clean_integer_kernel> rep_;
public:
	/*
	 big_integer_kernel is modeled by integer
	 */
	// The "base" of the number
	static const int RADIX = 10;
	
	t_integer_kernel(long n = 0): rep_(std::make_unique<I>(n)) {
		static_assert(std::is_base_of<clean_integer_kernel, I>::value,
                      "Implementation type of t_big_integer_kernel must derive from big_integer_kernel");
	}
	
	t_integer_kernel(const t_integer_kernel<I> &other) = delete;
	t_integer_kernel(t_integer_kernel<I>&& other): rep_(std::move(other.rep_)) {
		static_assert(std::is_base_of<clean_integer_kernel, I>::value,
                      "Implementation type of t_big_integer_kernel must derive from big_integer_kernel");
		other.rep_ = std::make_unique<I>();
	}
	
	t_integer_kernel<I>& operator=(const t_integer_kernel<I>& other) = delete;
	t_integer_kernel<I>& operator=(t_integer_kernel<I>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<I>();
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
	bool operator==(t_integer_kernel<I> &other) {
		return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, t_integer_kernel<I>& o) {
		return out << *o.rep_;
	}
};

template<typename I>
class t_integer: public t_integer_kernel<I> {
public:
	
	t_integer(long n = 0): t_integer_kernel<I>(n) {
		static_assert(std::is_base_of<clean_integer, I>::value,
                      "Implementation type of t_big_integer must derive from big_integer");
	}
	
	t_integer(const t_integer<I>& other) = delete;
	t_integer(t_integer<I>&& other): t_integer_kernel<I>(std::forward<t_integer_kernel<I>&&>(other)) {
		static_assert(std::is_base_of<clean_integer, I>::value,
					  "Implementation type of t_big_integer must derive from big_integer");
		other.rep_ = std::make_unique<I>();
	}
	
	t_integer<I>& operator=(const t_integer<I>& other) = delete;
	t_integer<I>& operator=(t_integer<I>&& other) {
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
		std::unique_ptr<clean_integer> casted(static_cast<clean_integer*>(this->rep_.release()));
		
        casted->increment();
		
        this->rep_ = std::move(casted);
	}
	
	/*
	 updates this
	 ensures this = #this - 1
	 */
	void decrement() {
		std::unique_ptr<clean_integer> casted(static_cast<clean_integer*>(this->rep_.release()));
		
        casted->decrement();
		
        this->rep_ = std::move(casted);
	}
	
	/*
	 replaces this
	 ensures  this = n
	 */
	void set_from_long(long n) {
		std::unique_ptr<clean_integer> casted(static_cast<clean_integer*>(this->rep_.release()));
        
		casted->set_from_long(n);
		
        this->rep_ = std::move(casted);
	}
    
	/*
	 requires 0 <= d and d < 10
	 ensures  this = |#this| and abs = [POSITIVE, ZERO, or NEGATIVE as this > 0, = 0, or < 0]
	 */
	integer_sign abs() {
		std::unique_ptr<clean_integer> casted(static_cast<clean_integer*>(this->rep_.release()));
        
		integer_sign sign = casted->abs();
		
        this->rep_ = std::move(casted);
		return sign;
	}
	
	/*
	 updates  this
	 ensures  sign = NEGATIVE ==> this = -|#this| and
	 sign = ZERO     ==> this = #this and
	 sign = POSITIVE ==> this = |#this|
	 */
	void assign_sign(integer_sign sign){
		std::unique_ptr<clean_integer> casted(static_cast<clean_integer*>(this->rep_.release()));
        
		casted->assign_sign(sign);
		
        this->rep_ = std::move(casted);
	}
	
	/*
	 ensures clone = this
	 */
	t_integer<I> clone() {
		t_integer<I> clone;
		std::unique_ptr<clean_integer> casted(static_cast<clean_integer*>(this->rep_.release()));
        
		clone.rep_ = casted->clone();
		
        this->rep_ = std::move(casted);
		return clone;
	}
	
	/*
	 updates  x
	 ensures  x = #x + y
	 */
	template<typename I2>
	friend t_integer<I> add(t_integer<I>&& x, t_integer<I2> &y) {
        t_integer<I> sum(std::forward<t_integer<I>>(x));
        
        std::unique_ptr<clean_integer> sum_casted(static_cast<clean_integer*>(sum.rep_.release()));
        std::unique_ptr<clean_integer> y_casted(static_cast<clean_integer*>(y.rep_.release()));
        
        sum_casted = add(std::move(sum_casted), y_casted);
        
        y.rep_ = std::move(y_casted);
        sum.rep_ = std::move(sum_casted);

        return sum;
	}
	
	/*
	 updates x
	 ensures x = #x - y
	 */
	template<typename I2>
	friend t_integer<I> subtract(t_integer<I>&& x, t_integer<I2> &y){
		t_integer<I> diff(std::forward<t_integer<I>>(x));
		
		std::unique_ptr<clean_integer> diff_casted(static_cast<clean_integer*>(diff.rep_.release()));
		std::unique_ptr<clean_integer> y_casted(static_cast<clean_integer*>(y.rep_.release()));
        
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
	template<typename I2>
	friend int compare(t_integer<I> &x, t_integer<I2> &y) {
		int comp;
		
		std::unique_ptr<clean_integer> x_casted(static_cast<clean_integer*>(x.rep_.release()));
		std::unique_ptr<clean_integer> y_casted(static_cast<clean_integer*>(y.rep_.release()));
        
		comp = compare(x_casted, y_casted);
		
        y.rep_ = std::move(y_casted);
		x.rep_ = std::move(x_casted);
		
		return comp;
	}
		
};

}

#endif /* template_integer_h */
