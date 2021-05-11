//
//  flexible_integer.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/13/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef flexible_integer_h
#define flexible_integer_h

// #include "integer_impl.hpp"
// #include "nn_integer.hpp"
#include <integer_impl/integer_impl.hpp>
#include <integer_impl/nn_integer.hpp>

namespace cleanpp
{


class integer_kernel : public clean_base {
protected:
	typedef nn_integer _flex_int_def_t;
	std::unique_ptr<integer_kernel_impl> rep_;
public:
	/*
	 big_integer_kernel is modeled by integer
	 */

	 // The "base" of the number
	static const int RADIX = 10;

	/*
	 initialization ensures this = n
	 */
	integer_kernel(long n = 0) {
		rep_ = std::make_unique<_flex_int_def_t>(n);
	}

	template<typename I>
	integer_kernel(__attribute__((unused)) const I& impl, long n = 0) {
		static_assert(std::is_base_of<integer_kernel_impl, I>::value,
			"Type of impl must derive from big_integer_kernel");
		rep_ = std::make_unique<I>(n);
	}

	integer_kernel(const integer_kernel& other) = delete;
	/*
	 clears other
	 initialization ensures this = #other
	 */
	integer_kernel(integer_kernel&& other) : rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<_flex_int_def_t>();
	}

	integer_kernel& operator=(const integer_kernel& other) = delete;
	/*
	 clears other
	 ensures this = #other
	 */
	integer_kernel& operator=(integer_kernel&& other) {
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
	bool operator==(integer_kernel& other) {
		return *this->rep_ == *other.rep_;
	}

	friend std::ostream& operator<<(std::ostream& out, integer_kernel& o) {
		return out << *o.rep_;
	}
};

class integer : public integer_kernel {
public:
	/*
	 initialization ensures this = n
	 */
	integer(long n = 0) : integer_kernel(n) { }

	template<typename I>
	integer(__attribute__((unused)) const I& impl, long n = 0) : integer_kernel(impl, n) {
		static_assert(std::is_base_of<integer_impl, I>::value,
			"Type of impl must derive from big_integer");
	}

	integer(const integer& other) = delete;
	/*
	 clears other
	 initialization ensures this = #other
	 */
	integer(integer&& other) : integer_kernel(std::forward<integer_kernel>(other)) { }

	integer& operator=(const integer& other) = delete;
	/*
	 clears this
	 ensures this = #other
	 */
	integer& operator=(integer&& other) {
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
		std::unique_ptr<integer_impl> casted(static_cast<integer_impl*>(this->rep_.release()));

		casted->increment();

		this->rep_ = std::move(casted);
	}

	/*
	 updates this
	 ensures this = #this - 1
	 */
	void decrement() {
		std::unique_ptr<integer_impl> casted(static_cast<integer_impl*>(this->rep_.release()));

		casted->decrement();

		this->rep_ = std::move(casted);
	}

	/*
	 replaces this
	 ensures  this = n
	 */
	void set_from_long(long n) {
		std::unique_ptr<integer_impl> casted(static_cast<integer_impl*>(this->rep_.release()));

		casted->set_from_long(n);

		this->rep_ = std::move(casted);
	}

	/*
	 requires 0 <= d and d < 10
	 ensures  this = |#this| and abs = [POSITIVE, ZERO, or NEGATIVE as this > 0, = 0, or < 0]
	 */
	integer_sign abs() {
		std::unique_ptr<integer_impl> casted(static_cast<integer_impl*>(this->rep_.release()));

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
	void assign_sign(integer_sign sign) {
		std::unique_ptr<integer_impl> casted(static_cast<integer_impl*>(this->rep_.release()));

		casted->assign_sign(sign);

		this->rep_ = std::move(casted);
	}

	/*
	 ensures clone = this
	 */
	integer clone() {
		integer clone(_flex_int_def_t{});
		std::unique_ptr<integer_impl> casted(static_cast<integer_impl*>(this->rep_.release()));

		clone.rep_ = casted->clone();

		this->rep_ = std::move(casted);
		return clone;
	}

	/*
	 ensures  add = #x + y
	 */
	friend std::tuple<integer, integer> add(integer&& x, integer&& y) {
		integer sum(std::forward<integer>(x));

		std::unique_ptr<integer_impl> sum_casted(static_cast<integer_impl*>(sum.rep_.release()));
		std::unique_ptr<integer_impl> y_casted(static_cast<integer_impl*>(y.rep_.release()));

		std::tie(sum_casted, y_casted) = add(std::move(sum_casted), std::move(y_casted));

		y.rep_ = std::move(y_casted);
		sum.rep_ = std::move(sum_casted);

		return std::make_tuple(std::move(sum), std::move(y));
	}

	/*
	 ensures subtract = #x - y
	 */
	friend std::tuple<integer, integer> subtract(integer&& x, integer&& y) {
		integer diff(std::forward<integer>(x));

		std::unique_ptr<integer_impl> diff_casted(static_cast<integer_impl*>(diff.rep_.release()));
		std::unique_ptr<integer_impl> y_casted(static_cast<integer_impl*>(y.rep_.release()));

		std::tie(diff_casted, y_casted) = subtract(std::move(diff_casted), std::move(y_casted));

		y.rep_ = std::move(y_casted);
		diff.rep_ = std::move(diff_casted);

		return std::make_tuple(std::move(diff), std::move(y));
	}

	/*
	 ensures compare > 0 ==> x > y and
	 compare = 0 ==> x = y and
	 compare < 0 ==> x < y
	 */
	friend std::tuple<int, integer, integer> compare(integer&& x, integer&& y) {
		int comp;

		std::unique_ptr<integer_impl> x_casted(static_cast<integer_impl*>(x.rep_.release()));
		std::unique_ptr<integer_impl> y_casted(static_cast<integer_impl*>(y.rep_.release()));

		std::tie(comp, x_casted, y_casted) = compare(std::move(x_casted), std::move(y_casted));

		y.rep_ = std::move(y_casted);
		x.rep_ = std::move(x_casted);

		return std::make_tuple(comp, std::move(x), std::move(y));
	}

};

}

#endif /* flexible_integer_h */
