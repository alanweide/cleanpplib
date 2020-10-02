//
//  natural_number.cpp
//  Cleanpp
//
//  Created by Alan Weide on 1/29/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <stdio.h>
#include <clean_nn/natural_number.hpp>

namespace cleanpp {

// natural_number_kernel
bool natural_number_kernel::operator==(natural_number_kernel &other) {
    bool ans = false;
    std::cout << *this;
    bool otherZero = other.is_zero();
    bool thisZero = (*this).is_zero();
	if (otherZero && thisZero) {
		ans = true;
	} else if (otherZero == thisZero) {
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

std::ostream& operator<<(std::ostream& out, natural_number_kernel& o) {
	if (o.is_zero()) {
		out << 0;
	} else {
		int d;
		d = o.divide_by_radix();
		if (!o.is_zero()) {
			out << o;
		}
		out << d;
		o.multiply_by_radix(d);
	}
	return out;
}

// natural_number_secondary
void natural_number_secondary::increment() {
	int d = 0;
	d = this->divide_by_radix();
	d++;
	if (d == RADIX) {
		d -= RADIX;
		increment();
	}
	multiply_by_radix(d);
}

void natural_number_secondary::decrement() {
	assert(!is_zero());
	int d = 0;
	d = this->divide_by_radix();
	d--;
	if (d < 0) {
		d += RADIX;
		decrement();
	}
	multiply_by_radix(d);
}

void natural_number_secondary::set_from_long(long n) {
    assert(n >= 0);
    if (n == 0) {
        clear();
    } else {
        long nLeft = n / RADIX;
        set_from_long(nLeft);
        multiply_by_radix(n % RADIX);
    }
}

/*
 const parameter: preserves
 pass-by-ref:     restores
 pass-by-move:    non-restores-mode
	 pass-by-move w/corresponding return:   updates
	 pass-by-move w/o corresponding return: clears
 returned w/o corresponding parameter: replaces
 receiver: ???
 
 what about?
 one parameter is a function call involving x
 add(std::move(x), f(x)):
 { $0 = std::move(x); $1 = f(x); add($0, $1); }?
 { $1 = f(x); add(std::move(x), $1); }?
 
 */

std::unique_ptr<natural_number_secondary>&& add(std::unique_ptr<natural_number_secondary> x, std::unique_ptr<natural_number_secondary> &y) {
    int x_low;
    x_low = x->divide_by_radix();
    int y_low;
    y_low = y->divide_by_radix();
    if (!y->is_zero()) {
        x = add(std::move(x), y);
    }
    x_low += y_low;
    if (x_low >= natural_number_secondary::RADIX) {
        x_low -= natural_number_secondary::RADIX;
        x->increment();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);
    return std::move(x);
}

std::unique_ptr<natural_number_secondary>&& subtract(std::unique_ptr<natural_number_secondary> x, std::unique_ptr<natural_number_secondary> &y) {
    int x_low;
    x_low = x->divide_by_radix();
    int y_low;
    y_low = y->divide_by_radix();
    if (!y->is_zero()) {
        x = subtract(std::move(x), y);
    }
    x_low -= y_low;
    if (x_low < 0) {
        x_low += natural_number_secondary::RADIX;
        x->decrement();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);
    return std::move(x);
}

}
