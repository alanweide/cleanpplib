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

void natural_number::increment() {
    int d = 0;
    divide_by_radix(d);
    d++;
    if (d == RADIX) {
        d -= RADIX;
        increment();
    }
    multiply_by_radix(d);
}

void natural_number::decrement() {
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

void natural_number::set_from_int(int n) {
    assert(n >= 0);
    if (n == 0) {
        clear();
    } else {
        int nLeft = n / RADIX;
        set_from_int(nLeft);
        multiply_by_radix(n % RADIX);
    }
}

void add(natural_number &x, natural_number &y) {
    int x_low;
    x.divide_by_radix(x_low);
    int y_low;
    y.divide_by_radix(y_low);
    if (!y.is_zero()) {
        add(x, y);
    }
    x_low += y_low;
    if (x_low >= natural_number::RADIX) {
        x_low -= natural_number::RADIX;
        x.increment();
    }
    x.multiply_by_radix(x_low);
    y.multiply_by_radix(y_low);
}

void subtract(natural_number &x, natural_number &y) {
    int x_low;
    x.divide_by_radix(x_low);
    int y_low;
    y.divide_by_radix(y_low);
    if (!y.is_zero()) {
        subtract(x, y);
    }
    x_low -= y_low;
    if (x_low < 0) {
        x_low += natural_number::RADIX;
        x.decrement();
    }
    x.multiply_by_radix(x_low);
    y.multiply_by_radix(y_low);
}

}
