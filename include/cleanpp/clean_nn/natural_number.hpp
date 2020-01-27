//
//  natural_number.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef natural_number_h
#define natural_number_h

#include "natural_number_kernel.hpp"

namespace cleanpp {
class natural_number: public natural_number_kernel {
public:    
    virtual void increment() {
        int d = 0;
        divide_by_radix(d);
        d++;
        if (d == RADIX) {
            d -= RADIX;
            increment();
        }
        multiply_by_radix(d);
    }
    virtual void decrement() {
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
    virtual void set_from_int(int n) {
        assert(n >= 0);
        if (n == 0) {
            clear();
        } else {
            int nLeft = n / RADIX;
            set_from_int(nLeft);
            multiply_by_radix(n % RADIX);
        }
    }
};
}

#endif /* natural_number_h */
