//
//  big_integer.cpp
//  Cleanpp
//
//  Created by Alan Weide on 2/10/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <clean_integer/big_integer.hpp>

namespace cleanpp {

// big_integer_kernel
bool big_integer_kernel::operator==(big_integer_kernel &other) {
	bool ans = false;
	if (other.sign() == ZERO && this->sign() == ZERO) {
		ans = true;
	} else if (other.sign() == this->sign()) {
		int last_this, last_other;
		this->divide_by_radix(last_this);
		other.divide_by_radix(last_other);
		if (last_this == last_other) {
			ans = *this == other;
		}
		this->multiply_by_radix(last_this);
		other.multiply_by_radix(last_other);
	}
	return ans;
}

std::ostream& operator<<(std::ostream& out, big_integer_kernel& o) {
	bool didNegate = false;
	if (o.sign() == big_integer_kernel::NEGATIVE) {
		out << '-';
		o.negate();
		didNegate = true;
	}
	if (o.sign() == big_integer_kernel::ZERO) {
		out << 0;
	} else {
		int d;
		o.divide_by_radix(d);
		if (o.sign() != big_integer_kernel::ZERO) {
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

// big_integer
void big_integer::increase_magnitude() {
	int d = 0;
	divide_by_radix(d);
	d++;
	if (d == big_integer::RADIX) {
		d -= big_integer::RADIX;
		increment();
	}
	multiply_by_radix(d);
}

void big_integer::decrease_magnitude() {
	assert(sign() != big_integer::ZERO);
	int d = 0;
	divide_by_radix(d);
	d--;
	if (d < 0) {
		d += big_integer::RADIX;
		decrement();
	}
	multiply_by_radix(d);
}

void big_integer::increment() {
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

void big_integer::decrement() {
	switch (this->sign()) {
		case NEGATIVE:
		case ZERO:
			increase_magnitude();
			break;
		case POSITIVE:
			decrease_magnitude();
			break;
	}
}

void big_integer::set_from_int(int n) {
	bool shouldNegate = false;
	if (n < 0) {
		n *= -1;
		shouldNegate = true;
	}
	
	if (n == 0) {
		clear();
	} else {
		int nLeft = n / RADIX;
		set_from_int(nLeft);
		multiply_by_radix(n % RADIX);
	}
	
	if (shouldNegate) {
		this->negate();
	}
}

//void add(big_integer &x, big_integer &y) {
//	int x_low;
//	x.divide_by_radix(x_low);
//	int y_low;
//	y.divide_by_radix(y_low);
//	if (!y.is_zero()) {
//		add(x, y);
//	}
//	x_low += y_low;
//	if (x_low >= big_integer::RADIX) {
//		x_low -= big_integer::RADIX;
//		x.increment();
//	}
//	x.multiply_by_radix(x_low);
//	y.multiply_by_radix(y_low);
//}
//
//void subtract(big_integer &x, big_integer &y) {
//	int x_low;
//	x.divide_by_radix(x_low);
//	int y_low;
//	y.divide_by_radix(y_low);
//	if (!y.is_zero()) {
//		subtract(x, y);
//	}
//	x_low -= y_low;
//	if (x_low < 0) {
//		x_low += big_integer::RADIX;
//		x.decrement();
//	}
//	x.multiply_by_radix(x_low);
//	y.multiply_by_radix(y_low);
//}
}
