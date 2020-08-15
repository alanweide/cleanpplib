//
//  template_integer.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/13/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef template_integer_h
#define template_integer_h

#include <clean_integer/big_integer.hpp>

namespace cleanpp {

template<typename I>
class t_big_integer_kernel;

template<typename I>
class t_big_integer;

template<typename I>
class t_big_integer_kernel: public clean_base {
private:
	std::unique_ptr<big_integer_kernel> rep_;
public:
	/*
	 big_integer_kernel is modeled by integer
	 */
	// The "base" of the number
	static const int RADIX = 10;
	
	t_big_integer_kernel(long n = 0): rep_(std::make_unique<I>(n)) {}
	
	t_big_integer_kernel(const t_big_integer_kernel<I> &other) = delete;
	t_big_integer_kernel(t_big_integer_kernel<I>&& other): rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<I>();
	}
	
	t_big_integer_kernel<I>& operator=(const t_big_integer_kernel<I>& other) = delete;
	t_big_integer_kernel<I>& operator=(t_big_integer_kernel<I>&& other) {
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
	bool operator==(t_big_integer_kernel<I> &other) {
		return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, t_big_integer_kernel<I>& o) {
		return out << *o.rep_;
	}
	
	friend class t_big_integer<I>;
};

template<typename I>
class t_big_integer: public t_big_integer_kernel<I> {
private:
//	template<typename I2>
//	friend int compare_magnitude(t_big_integer<I> &x, t_big_integer<I2> &y) {
//		integer_sign x_sign = x.abs();
//		integer_sign y_sign = y.abs();
//		int comp = compare(x, y);
//		x.assign_sign(x_sign);
//		y.assign_sign(y_sign);
//		return comp;
//	}
//
//	/*
//	 updates this
//	 ensures |this| = |#this| + 1 and
//	 this < 0 iff #this < 0
//	 */
//	void increase_magnitude() {
//		std::unique_ptr<big_integer> casted(dynamic_cast<big_integer*>(this->rep_.release()));
//		casted->increase_magnitude();
//		this->rep_ = std::move(casted);
//	}
//
//	/*
//	 updates  this
//	 requires this != 0
//	 ensures  |this| = |#this| - 1 and
//	 this < 0 iff #this < 0
//	 */
//	void decrease_magnitude() {
//		assert(this->sign() != ZERO);
//
//		std::unique_ptr<big_integer> casted(dynamic_cast<big_integer*>(this->rep_.release()));
//		casted->decrease_magnitude();
//		this->rep_ = std::move(casted);
//	}
//
//	/*
//	 updates  x
//	 requires (x > 0 ==> y >= 0) and (x < 0 ==> y <= 0)
//	 ensures  |x| = |#x| + |y| and (x >= 0 iff #x >= 0)
//	 */
//	template<typename I2>
//	friend t_big_integer<I> combine_same(t_big_integer<I>&& x, t_big_integer<I2> &y) {
//		assert(x.sign() == y.sign() || x.sign() == ZERO || y.sign() == ZERO);
//
//		integer_sign x_sign = x.abs(), y_sign = y.abs();
//
//		int x_low = x.divide_by_radix();
//		int y_low = y.divide_by_radix();
//		if (y.sign() != ZERO) {
//			x = combine_same(std::move(x), y);
//		}
//		x_low += y_low;
//		if (x_low >= t_big_integer::RADIX) {
//			x_low -= t_big_integer::RADIX;
//			x.increase_magnitude();
//		}
//		x.multiply_by_radix(x_low);
//		y.multiply_by_radix(y_low);
//
//		integer_sign new_x_sign = (x_sign == 0 ? y_sign : x_sign);
//		x.assign_sign(new_x_sign);
//
//		y.assign_sign(y_sign);
//
//		return std::move(x);
//	}
//
//
//	/*
//	 updates  x
//	 requires (x > 0 ==> y <= 0) and (x < 0 ==> y >= 0)
//	 ensures  |x| = |#x| - |y| and (x >= 0 iff #x >= y)
//	 */
//	template<typename I2>
//	friend t_big_integer<I> combine_different(t_big_integer<I>&& x, t_big_integer<I2> &y) {
//		assert(x.sign() != y.sign() || x.sign() == ZERO);
//
//		int mag_comp = compare_magnitude(x, y);
//		if (mag_comp > 0) {
//			x = remove(std::move(x), y);
//		} else if (mag_comp < 0) {
//			t_big_integer<I> tmp = std::move(x);
//			x = y.clone();
//			x = remove(std::move(x), tmp);
//		} else {
//			x.clear();
//		}
//
//		return std::move(x);
//	}
//
//	/*
//	 updates  x
//	 requires |x| > |y|
//	 ensures  |x| = |#x| - |y| and (x >= 0 iff #x >= 0)
//	 */
//	template<typename I2>
//	friend t_big_integer<I> remove(t_big_integer<I>&& x, t_big_integer<I2> &y) {
//		assert(compare_magnitude(x, y) > 0);
//
//		integer_sign x_sign = x.abs(), y_sign = y.abs();
//
//		int x_low = x.divide_by_radix();
//		int y_low = y.divide_by_radix();
//		if (y.sign() != ZERO) {
//			x = remove(std::move(x), y);
//		}
//		x_low -= y_low;
//		if (x_low < 0) {
//			x_low += big_integer::RADIX;
//			x.decrease_magnitude();
//		}
//		x.multiply_by_radix(x_low);
//		y.multiply_by_radix(y_low);
//
//		x.assign_sign(x_sign);
//		y.assign_sign(y_sign);
//
//		return std::move(x);
//	}

public:
	
	t_big_integer(long n = 0): t_big_integer_kernel<I>(n) {
		static_assert(std::is_base_of<big_integer, I>::value,
					  "Template parameter I must derive from big_integer");
	}
	
	t_big_integer(const t_big_integer<I>& other) = delete;
	t_big_integer(t_big_integer<I>&& other): t_big_integer_kernel<I>(std::move(other)) {
		static_assert(std::is_base_of<big_integer, I>::value,
					  "Template parameter I must derive from big_integer");
		other.rep_ = std::make_unique<I>();
	}
	
	t_big_integer<I>& operator=(const t_big_integer<I>& other) = delete;
	t_big_integer<I>& operator=(t_big_integer<I>&& other) {
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
		std::unique_ptr<big_integer> casted(dynamic_cast<big_integer*>(this->rep_.release()));
		casted->increment();
		this->rep_ = std::move(casted);
	}
	
	/*
	 updates this
	 ensures this = #this - 1
	 */
	void decrement() {
		std::unique_ptr<big_integer> casted(dynamic_cast<big_integer*>(this->rep_.release()));
		casted->decrement();
		this->rep_ = std::move(casted);
	}
	
	/*
	 replaces this
	 ensures  this = n
	 */
	void set_from_long(long n) {
		std::unique_ptr<big_integer> casted(dynamic_cast<big_integer*>(this->rep_.release()));
		casted->set_from_long(n);
		this->rep_ = std::move(casted);
	}
	
	/*
	 requires 0 <= d and d < 10
	 ensures  this = |#this| and abs = [POSITIVE, ZERO, or NEGATIVE as this > 0, = 0, or < 0]
	 */
	integer_sign abs() {
		std::unique_ptr<big_integer> casted(dynamic_cast<big_integer*>(this->rep_.release()));
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
		std::unique_ptr<big_integer> casted(dynamic_cast<big_integer*>(this->rep_.release()));
		casted->assign_sign(sign);
		this->rep_ = std::move(casted);
	}
	
	/*
	 ensures clone = this
	 */
	t_big_integer<I> clone() {
		t_big_integer<I> clone;
		std::unique_ptr<big_integer> casted(dynamic_cast<big_integer*>(this->rep_.release()));
		clone.rep_ = casted->clone();
		this->rep_ = std::move(casted);
		return clone;
	}
	
	/*
	 updates  x
	 ensures  x = #x + y
	 */
	template<typename I2>
	friend t_big_integer<I> add(t_big_integer<I>&& x, t_big_integer<I2> &y) {
		t_big_integer<I> sum;
		
		std::unique_ptr<big_integer> x_casted(dynamic_cast<big_integer*>(x.rep_.release()));
		std::unique_ptr<big_integer> y_casted(dynamic_cast<big_integer*>(y.rep_.release()));
		sum.rep_ = add(std::move(x_casted), y_casted);
		y.rep_ = std::move(y_casted);
		x.rep_ = std::move(x_casted);

		return sum;
	}
	
	/*
	 updates x
	 ensures x = #x - y
	 */
	template<typename I2>
	friend t_big_integer<I> subtract(t_big_integer<I>&& x, t_big_integer<I2> &y){
		t_big_integer<I> sum;
		
		std::unique_ptr<big_integer> x_casted(dynamic_cast<big_integer*>(x.rep_.release()));
		std::unique_ptr<big_integer> y_casted(dynamic_cast<big_integer*>(y.rep_.release()));
		sum.rep_ = subtract(std::move(x_casted), y_casted);
		y.rep_ = std::move(y_casted);
		x.rep_ = std::move(x_casted);
		
		return sum;
	}
	
	/*
	 ensures compare > 0 ==> x > y and
	 compare = 0 ==> x = y and
	 compare < 0 ==> x < y
	 */
	template<typename I2>
	friend int compare(t_big_integer<I> &x, t_big_integer<I2> &y) {
		int comp;
		
		std::unique_ptr<big_integer> x_casted(dynamic_cast<big_integer*>(x.rep_.release()));
		std::unique_ptr<big_integer> y_casted(dynamic_cast<big_integer*>(y.rep_.release()));
		comp = compare(x_casted, y_casted);
		y.rep_ = std::move(y_casted);
		x.rep_ = std::move(x_casted);
		
		return comp;
	}
};

}

#endif /* template_integer_h */
