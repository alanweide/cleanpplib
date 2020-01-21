//
//  NaturalNumberKernel.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef NaturalNumberKernel_hpp
#define NaturalNumberKernel_hpp

#include <stdio.h>
#include "CleanBase.hpp"

namespace cleanpp {
class natural_number_kernel: public clean_base<void> {
public:
    static const int RADIX = 10;
    virtual bool is_zero() = 0;
    virtual void multiply_by_radix(int digit) = 0;
    virtual void divide_by_radix(int &digit) = 0;
    virtual bool operator==(natural_number_kernel &other) {
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
};
}

#endif /* NaturalNumberKernel_hpp */
