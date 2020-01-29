//
//  natural_number_kernel.cpp
//  Cleanpp
//
//  Created by Alan Weide on 1/29/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <stdio.h>
#include <clean_nn/natural_number_kernel.hpp>

namespace cleanpp {
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

}
