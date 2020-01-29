//
//  natuarl_number_kernel.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef natural_number_kernel_h
#define natural_number_kernel_h

#include <stdio.h>
#include <clean_base.hpp>

namespace cleanpp {
class natural_number_kernel: public clean_base {
public:
    static const int RADIX = 10;
    
    virtual bool is_zero() = 0;
    virtual void multiply_by_radix(int digit) = 0;
    virtual void divide_by_radix(int &digit) = 0;
    
    bool operator==(natural_number_kernel &other) {
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
    
    friend std::ostream& operator<<(std::ostream& out, natural_number_kernel& o) {
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
};
}

#endif /* natural_number_kernel_h */
