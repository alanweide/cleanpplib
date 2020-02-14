//
//  big_integer.cpp
//  Cleanpp
//
//  Created by Alan Weide on 2/10/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <clean_integer/big_integer.hpp>

namespace cleanpp {

/* ----------------------------
* helper functions
* ---------------------------- */

int compare(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    if (x->sign() > y->sign()) {
        return 1;
    } else if (x->sign() < y->sign()) {
        return -1;
    } else if (x->sign() == ZERO && y->sign() == ZERO) {
        return 0;
    } else {
        int x_low, y_low;
        x->divide_by_radix(x_low);
        y->divide_by_radix(y_low);
        int comp = compare(x, y);
        if (comp == 0) {
            comp = x_low - y_low;
        }
        x->multiply_by_radix(x_low);
        y->multiply_by_radix(y_low);
        return comp;
    }
}

int compare_magnitude(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    integer_sign x_sign = x->abs();
    integer_sign y_sign = y->abs();
    int comp = compare(x, y);
    x->assign_sign(x_sign);
    y->assign_sign(y_sign);
    return comp;
}

/* ----------------------------
* big_integer_kernel
* ---------------------------- */

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
    if (o.sign() == NEGATIVE) {
        out << '-';
        o.negate();
        didNegate = true;
    }
    
    if (o.sign() == ZERO) {
        out << 0;
    } else {
        int d;
        o.divide_by_radix(d);
        if (o.sign() != ZERO) {
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

/* ----------------------------
* big_integer
* ---------------------------- */

void big_integer::increase_magnitude() {
    int d;
    
    integer_sign sign = this->abs();
    
    divide_by_radix(d);
    d++;
    if (d == big_integer::RADIX) {
        d -= big_integer::RADIX;
        increase_magnitude();
    }
    multiply_by_radix(d);
    
    if (sign != ZERO) {
        this->assign_sign(sign);
    }
}

void big_integer::decrease_magnitude() {
    assert(sign() != ZERO);
    
    integer_sign sign = this->abs();
    
    int d = 0;
    divide_by_radix(d);
    d--;
    if (d < 0) {
        d += big_integer::RADIX;
        decrease_magnitude();
    }
    multiply_by_radix(d);
    
    if (this->sign() != ZERO) {
        this->assign_sign(sign);
    }
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
            increase_magnitude();
            break;
        case ZERO:
            increase_magnitude();
            negate();
            break;
        case POSITIVE:
            decrease_magnitude();
            break;
    }
}

void big_integer::set_from_int(int n) {
    bool shouldNegate = n < 0;
    if (shouldNegate) {
        n *= -1;
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

integer_sign big_integer::abs() {
    integer_sign sign = this->sign();
    if (sign == NEGATIVE) {
        negate();
    }
    return sign;
}

void big_integer::assign_sign(integer_sign sign) {
    assert((this->sign() == ZERO) == (sign == ZERO));

    if (this->sign() != sign) {
        this->negate();
    }
}

std::unique_ptr<big_integer> big_integer::clone() {
    std::unique_ptr<big_integer> clone;
    if (this->sign() == ZERO) {
        clone = this->new_instance();
    } else {
        integer_sign this_sign = this->abs();
        
        int d;
        this->divide_by_radix(d);
        
        clone = this->clone();
        
        clone->multiply_by_radix(d);
        this->multiply_by_radix(d);
        
        clone->assign_sign(this_sign);
        this->assign_sign(this_sign);
    }
    return clone;
}

/* ----------------------------
 * friend functions
 * ---------------------------- */

void combine_same(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    assert(x->sign() == y->sign() || x->sign() == ZERO || y->sign() == ZERO);

    int x_low, y_low;
    x->divide_by_radix(x_low);
    y->divide_by_radix(y_low);
    if (y->sign() != ZERO) {
        combine_same(x, y);
    }
    x_low += y_low;
    if (x_low >= big_integer::RADIX) {
        x_low -= big_integer::RADIX;
        x->increase_magnitude();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);
}

void remove(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    assert(compare_magnitude(x, y) > 0);
    
    integer_sign sign = y->abs();
    
    int x_low, y_low;
    x->divide_by_radix(x_low);
    y->divide_by_radix(y_low);
    if (y->sign() != ZERO) {
        remove(x, y);
    }
    x_low -= y_low;
    if (x_low < 0) {
        x_low += big_integer::RADIX;
        x->decrease_magnitude();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);
    
    y->assign_sign(sign);
}

void combine_different(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    assert(x->sign() != y->sign() || x->sign() == ZERO);

    if (compare_magnitude(x, y) > 0) {
        remove(x, y);
    } else if (compare_magnitude(x, y) < 0) {
        std::unique_ptr<big_integer> tmp = x->new_instance();
        std::swap(x, tmp);
        x = y->clone();
        remove(x, tmp);
    } else {
        x->clear();
    }
}

void add(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    //updates x
    //ensure x = #x + y

    if (x->sign() == ZERO || x->sign() == y->sign()) {
        combine_same(x, y);
    } else {
        combine_different(x, y);
    }
}

void subtract(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    //updates x
    //ensures x = #x - y

    y->negate();
    add(x, y);
    y->negate();
}

}
