//
//  natural_number.cpp
//  Cleanpp
//
//  Created by Alan Weide on 1/29/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <memory>
#include <assert.h>
#include <stdio.h>
#include <clean_nn/natural_number.hpp>
#include <bounded_nn.hpp>


namespace cleanpp {

// natural_number_kernel
bool natural_number_kernel_impl::operator==(natural_number_kernel_impl &other) {
    bool ans = false;
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

std::ostream& operator<<(std::ostream& out, natural_number_kernel_impl& o) {
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
void natural_number_impl::increment() {
    int d = 0;
    d = this->divide_by_radix();
    d++;
    if (d == RADIX) {
        d -= RADIX;
        increment();
    }
    multiply_by_radix(d);
}

void natural_number_impl::decrement() {
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

void natural_number_impl::set_from_long(long n) {
    assert(n >= 0);
    if (n == 0) {
        clear();
    } else {
        long nLeft = n / RADIX;
        set_from_long(nLeft);
        multiply_by_radix(n % RADIX);
    }
}

void natural_number_impl::divide_by_two() {
    if (!this->is_zero()) {
        int d = this->divide_by_radix();
        int parityChecker = this->divide_by_radix();
        this->multiply_by_radix(parityChecker);
        if (parityChecker % 2 != 0) {
            d += RADIX;
        }
        this->divide_by_two();
        d /= 2;
        this->multiply_by_radix(d);
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

std::unique_ptr<natural_number_impl> add(std::unique_ptr<natural_number_impl> x, std::unique_ptr<natural_number_impl> &y) {
    int x_low;
    x_low = x->divide_by_radix();
    int y_low;
    y_low = y->divide_by_radix();
    if (!y->is_zero()) {
        x = add(std::move(x), y);
    }
    x_low += y_low;
    if (x_low >= natural_number_impl::RADIX) {
        x_low -= natural_number_impl::RADIX;
        x->increment();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);
    return x;
}

std::unique_ptr<natural_number_impl>&& subtract(std::unique_ptr<natural_number_impl> x, std::unique_ptr<natural_number_impl> &y) {
    int x_low;
    x_low = x->divide_by_radix();
    int y_low;
    y_low = y->divide_by_radix();
    if (!y->is_zero()) {
        x = subtract(std::move(x), y);
    }
    x_low -= y_low;
    if (x_low < 0) {
        x_low += natural_number_impl::RADIX;
        x->decrement();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);
    return std::move(x);
}

std::unique_ptr<natural_number_impl> multiply_by_digit(std::unique_ptr<natural_number_impl> x, int d) {
    int last_dig = x->divide_by_radix();
    last_dig *= d;
    if (!x->is_zero()) {
        x = multiply_by_digit(std::move(x), d);
        x->multiply_by_radix(0);
    }
    std::unique_ptr<natural_number_impl> nn_last_dig(static_cast<natural_number_impl*>(x->new_instance().release()));
    nn_last_dig = add(std::move(nn_last_dig), x);
    nn_last_dig->set_from_long(last_dig);
    x = add(std::move(x), nn_last_dig);
    return x;
}

std::unique_ptr<natural_number_impl> multiply(std::unique_ptr<natural_number_impl> x, std::unique_ptr<natural_number_impl> &y) {
    if (y->is_zero()) {
        x->clear();
    } else {
        int y_ones = y->divide_by_radix();
        std::unique_ptr<natural_number_impl> x_copy(static_cast<natural_number_impl*>(x->new_instance().release()));
        x_copy = add(std::move(x_copy), x);
        x_copy = multiply_by_digit(std::move(x_copy), y_ones);
        x = multiply(std::move(x), y);
        x->multiply_by_radix(0);
        x = add(std::move(x), x_copy);
        y->multiply_by_radix(y_ones);
    }
    return x;
}



}
