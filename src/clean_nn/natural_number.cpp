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
	if (other.is_zero() && this->is_zero()) {
		ans = true;
	} else if (other.is_zero() == this->is_zero()) {
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

std::ostream& operator<<(std::ostream& out, natural_number_kernel& o) {
	if (o.is_zero()) {
		out << 0;
	} else {
		int d;
		o.divide_by_radix(d);
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
    divide_by_radix(d);
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
    divide_by_radix(d);
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
 pass-by-ref:  restores-mode
 pass-by-move: non-restores-mode
    pass-by-move w/corresponding return:   updates
    pass-by-move w/o corresponding return: clears
 returned w/o corresponding parameter: replaces
 
 what about?
    one parameter is a function call involving x
        add(std::move(x), f(x)):
        { $0 = std::move(x); $1 = f(x); add($0, $1); }?
        { $1 = f(x); add(std::move(x), $1); }?
    
 */
std::unique_ptr<natural_number_secondary>&& clearingAdd(std::unique_ptr<natural_number_secondary> x, std::unique_ptr<natural_number_secondary> &y) {
    int x_low;
    x->divide_by_radix(x_low);
    int y_low;
    y->divide_by_radix(y_low);
    if (!y->is_zero()) {
        x = clearingAdd(std::move(x), y);
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

void add(std::unique_ptr<natural_number_secondary> &x, std::unique_ptr<natural_number_secondary> &y) {
    int x_low;
    x->divide_by_radix(x_low);
    int y_low;
    y->divide_by_radix(y_low);
    if (!y->is_zero()) {
        add(x, y);
    }
    x_low += y_low;
    if (x_low >= natural_number_secondary::RADIX) {
        x_low -= natural_number_secondary::RADIX;
        x->increment();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);
}

void subtract(std::unique_ptr<natural_number_secondary> &x, std::unique_ptr<natural_number_secondary> &y) {
    int x_low;
    x->divide_by_radix(x_low);
    int y_low;
    y->divide_by_radix(y_low);
    if (!y->is_zero()) {
        subtract(x, y);
    }
    x_low -= y_low;
    if (x_low < 0) {
        x_low += natural_number_secondary::RADIX;
        x->decrement();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);
}

}
