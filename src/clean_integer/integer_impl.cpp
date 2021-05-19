//
//  big_integer.cpp
//  Cleanpp
//
//  Created by Alan Weide on 2/10/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <assert.h>
#include <memory>
#include <integer_impl/integer_impl.hpp>

namespace cleanpp
{

/* ----------------------------
* helper function(s)
* ---------------------------- */

/*
 ensures compare > 0 ==> |x| > |y| and
		 compare = 0 ==> |x| = |y| and
		 compare < 0 ==> |x| < |y|
 */
int compare_magnitude(std::unique_ptr<integer_impl>& x, std::unique_ptr<integer_impl>& y) {
	integer_sign x_sign = x->abs();
	integer_sign y_sign = y->abs();
	int comp = compare(x, y);
	x->assign_sign(x_sign);
	y->assign_sign(y_sign);
	return comp;
}

/* ----------------------------
* big_integer_kernel
* ---------------------------- */

bool integer_kernel_impl::operator==(integer_kernel_impl& other) {
	bool ans = false;
	if (other.sign() == ZERO && this->sign() == ZERO) {
		ans = true;
	} else if (other.sign() == this->sign()) {
		int last_this, last_other;
		last_this = this->divide_by_radix();
		last_other = other.divide_by_radix();
		if (last_this == last_other) {
			ans = *this == other;
		}
		this->multiply_by_radix(last_this);
		other.multiply_by_radix(last_other);
	}
	return ans;
}

std::ostream& operator<<(std::ostream& out, integer_kernel_impl& o) {
	bool didNegate = false;
	if (o.sign() == NEGATIVE) {
		out << '-';
		o.negate();
		didNegate = true;
	}

	if (o.sign() == ZERO) {
		out << 0;
	} else {
		int d;
		d = o.divide_by_radix();
		if (o.sign() != ZERO) {
			out << o;
		}
		out << d;
		o.multiply_by_radix(d);
	}

	if (didNegate) {
		o.negate();
	}
	return out;
}

/* ----------------------------
* big_integer
* ---------------------------- */

void integer_impl::increase_magnitude() {
	int d;

	integer_sign sign = this->abs();

	d = divide_by_radix();
	d++;
	if (d == integer_impl::RADIX) {
		d -= integer_impl::RADIX;
		increase_magnitude();
	}
	multiply_by_radix(d);

	this->assign_sign(sign);
}

void integer_impl::decrease_magnitude() {
	assert(sign() != ZERO);

	integer_sign sign = this->abs();

	int d = 0;
	d = divide_by_radix();
	d--;
	if (d < 0) {
		d += integer_impl::RADIX;
		decrease_magnitude();
	}
	multiply_by_radix(d);

	this->assign_sign(sign);
}

void integer_impl::increment() {
	switch (this->sign()) {
		case NEGATIVE:
			decrease_magnitude();
			break;
		case ZERO:
		case POSITIVE:
			increase_magnitude();
			break;
	}
}

void integer_impl::decrement() {
	switch (this->sign()) {
		case NEGATIVE:
			increase_magnitude();
			break;
		case ZERO:
			increase_magnitude();
			negate();
			break;
		case POSITIVE:
			decrease_magnitude();
			break;
	}
}

void integer_impl::set_from_long(long n) {
	bool shouldNegate = n < 0;
	if (shouldNegate) {
		n *= -1;
	}

	if (n == 0) {
		clear();
	} else {
		long nLeft = n / RADIX;
		set_from_long(nLeft);
		multiply_by_radix(n % RADIX);
	}

	if (shouldNegate) {
		this->negate();
	}
}

integer_sign integer_impl::abs() {
	integer_sign sign = this->sign();
	if (sign == NEGATIVE) {
		negate();
	}
	return sign;
}

void integer_impl::assign_sign(integer_sign sign) {
	if (this->sign() == -sign) {
		this->negate();
	}
}

std::unique_ptr<integer_impl> integer_impl::clone() {
	std::unique_ptr<integer_impl> clone;
	if (this->sign() == ZERO) {
		clone = this->new_instance();
	} else {
		integer_sign this_sign = this->abs();

		int d;
		d = this->divide_by_radix();

		clone = this->clone();

		clone->multiply_by_radix(d);
		this->multiply_by_radix(d);

		clone->assign_sign(this_sign);
		this->assign_sign(this_sign);
	}
	return clone;
}

/* ----------------------------
 * friend functions
 * ---------------------------- */

std::unique_ptr<integer_impl> combine_same(std::unique_ptr<integer_impl>&& x, std::unique_ptr<integer_impl>& y) {
	assert(x->sign() == y->sign() || x->sign() == ZERO || y->sign() == ZERO);

	integer_sign x_sign = x->abs(), y_sign = y->abs();

	int x_low, y_low;
	x_low = x->divide_by_radix();
	y_low = y->divide_by_radix();
	if (y->sign() != ZERO) {
		x = combine_same(std::move(x), y);
	}
	x_low += y_low;
	if (x_low >= integer_impl::RADIX) {
		x_low -= integer_impl::RADIX;
		x->increase_magnitude();
	}
	x->multiply_by_radix(x_low);
	y->multiply_by_radix(y_low);

	// This decision was key
	x->assign_sign(x_sign == 0 ? y_sign : x_sign);

	y->assign_sign(y_sign);

	return std::move(x);
}

std::unique_ptr<integer_impl> remove(std::unique_ptr<integer_impl>&& x, std::unique_ptr<integer_impl>& y) {
	assert(compare_magnitude(x, y) > 0);

	integer_sign x_sign = x->abs(), y_sign = y->abs();

	int x_low, y_low;
	x_low = x->divide_by_radix();
	y_low = y->divide_by_radix();
	if (y->sign() != ZERO) {
		x = remove(std::move(x), y);
	}
	x_low -= y_low;
	if (x_low < 0) {
		x_low += integer_impl::RADIX;
		x->decrease_magnitude();
	}
	x->multiply_by_radix(x_low);
	y->multiply_by_radix(y_low);

	x->assign_sign(x_sign);
	y->assign_sign(y_sign);

	return std::move(x);
}

std::unique_ptr<integer_impl> combine_different(std::unique_ptr<integer_impl>&& x, std::unique_ptr<integer_impl>& y) {
	assert(x->sign() != y->sign() || x->sign() == ZERO);

	if (compare_magnitude(x, y) > 0) {
		x = remove(std::move(x), y);
	} else if (compare_magnitude(x, y) < 0) {
		std::unique_ptr<integer_impl> tmp = std::move(x);
		x = y->clone();
		x = remove(std::move(x), tmp);
	} else {
		x->clear();
	}

	return std::move(x);
}

std::tuple<std::unique_ptr<integer_impl>, std::unique_ptr<integer_impl>, std::unique_ptr<integer_impl>> add(std::unique_ptr<integer_impl> x, std::unique_ptr<integer_impl> y) {

    std::unique_ptr<integer_impl> x_clone = x->clone();
    std::unique_ptr<integer_impl> sum;
    if (x->sign() == ZERO || x->sign() == y->sign()) {
        sum = combine_same(std::move(x), y);
        return std::make_tuple(std::move(sum), std::move(x_clone), std::move(y));
    } else {
        sum = combine_different(std::move(x), y);
        return std::make_tuple(std::move(sum), std::move(x_clone), std::move(y));
    }
}

std::tuple<std::unique_ptr<integer_impl>, std::unique_ptr<integer_impl>, std::unique_ptr<integer_impl>> subtract(std::unique_ptr<integer_impl> x, std::unique_ptr<integer_impl> y) {
    std::unique_ptr<integer_impl> diff;
    y->negate();
    std::tie(diff, x, y) = add(std::move(x), std::move(y));
    y->negate();
	
	return std::make_tuple(std::move(diff), std::move(x), std::move(y));
}

int compare(std::unique_ptr<integer_impl>& x, std::unique_ptr<integer_impl>& y) {
	if (x->sign() > y->sign()) {
		return 1;
	} else if (x->sign() < y->sign()) {
		return -1;
	} else if (x->sign() == ZERO && y->sign() == ZERO) {
		return 0;
	} else {
		integer_sign x_sign = x->abs(), y_sign = y->abs();
		int x_low, y_low;
		x_low = x->divide_by_radix();
		y_low = y->divide_by_radix();
		int comp = compare(x, y);
		if (comp == 0) {
			comp = x_low - y_low;
		}
		x->multiply_by_radix(x_low);
		y->multiply_by_radix(y_low);

		x->assign_sign(x_sign);
		y->assign_sign(y_sign);

		return comp * x_sign;
	}
}
}
