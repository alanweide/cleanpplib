//
//  NaturalNumber.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef NaturalNumber_h
#define NaturalNumber_h

#include "NaturalNumberKernel.hpp"

namespace cleanpp {
class natural_number: public natural_number_kernel {
public:
    virtual void increment() {
        int d = 0;
        this->divide_by_radix(d);
        d++;
        if (d == RADIX) {
            d -= RADIX;
            this->increment();
        }
        this->multiply_by_radix(d);
    }
    virtual void decrement() {
        int d = 0;
        this->divide_by_radix(d);
        d--;
        if (d == 0) {
            d += RADIX;
            this->decrement();
        }
        this->multiply_by_radix(d);
    }
    virtual void set_from_int(int n) {
        if (n == 0) {
            this->clear();
        } else {
            int nLeft = n / RADIX;
            this->set_from_int(nLeft);
            this->multiply_by_radix(n % RADIX);
        }
    }
};
}

#endif /* NaturalNumber_h */
