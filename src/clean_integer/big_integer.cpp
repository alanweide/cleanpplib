//
//  big_integer.cpp
//  Cleanpp
//
//  Created by Alan Weide on 2/10/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <clean_integer/big_integer.hpp>

namespace cleanpp {

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
        return comp * x->sign();
    }
}

// big_integer_kernel
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

// big_integer
void big_integer::increase_magnitude() {
    integer_sign old_sign = sign();
    
    int d;
    divide_by_radix(d);
    d++;
    if (d == big_integer::RADIX) {
        d -= big_integer::RADIX;
        increase_magnitude();
    }
    multiply_by_radix(d);
    
    if (old_sign == -sign()) {
        negate();
    }
}

void big_integer::decrease_magnitude() {
    assert(sign() != ZERO);
    
    integer_sign old_sign = sign();
    
    int d = 0;
    divide_by_radix(d);
    d--;
    if (d < 0) {
        d += big_integer::RADIX;
        decrease_magnitude();
    }
    multiply_by_radix(d);
    
    if (old_sign == -sign()) {
        negate();
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
    bool shouldNegate = false;
    if (n < 0) {
        n *= -1;
        shouldNegate = true;
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

// friend methods
void change_magnitude_up(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    assert(y->sign() >= ZERO);
    integer_sign old_x_sign = x->sign();

    int x_low, y_low;
    x->divide_by_radix(x_low);
    y->divide_by_radix(y_low);
    if (y->sign() != ZERO) {
        add(x, y);
    }
    x_low += y_low;
    if (x_low >= big_integer::RADIX) {
        x_low -= big_integer::RADIX;
        x->increase_magnitude();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);
    
    if (old_x_sign == -x->sign()) {
        x->negate();
    }
}

void change_magnitude_down(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    assert(y->sign() >= ZERO);
    integer_sign old_x_sign = x->sign();

    int x_low, y_low;
    x->divide_by_radix(x_low);
    y->divide_by_radix(y_low);
    if (y->sign() != ZERO) {
        subtract(x, y);
    }
    x_low -= y_low;
    if (x_low < 0) {
        x_low += big_integer::RADIX;
        x->decrease_magnitude();
    }
    x->multiply_by_radix(x_low);
    y->multiply_by_radix(y_low);

    if (old_x_sign == -x->sign()) {
        x->negate();
    }
}

void add(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
    if (x->sign() == ZERO || x->sign() == y->sign()) {
        integer_sign old_y_sign = y->abs();
        if (x->sign() == ZERO || old_y_sign == POSITIVE) {
            change_magnitude_up(x, y);
        } else if (x->sign() == old_y_sign) {
            change_magnitude_up(x, y);
        } else {
            change_magnitude_down(x, y);
        }
        y->assign_sign(old_y_sign);
    } else if (y->sign() != ZERO) {
        y->negate();
        subtract(x, y);
        y->negate();
    }
    if (y->sign() != ZERO) {
    }
}

void subtract(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y) {
        if (x->sign() == ZERO || x->sign() == y->sign()) {
            bool swapped = false;
            if (compare(x, y) * y->sign() < 0) {
                swapped = true;
                std::swap(x, y);
            }
            
            integer_sign old_y_sign = y->abs();
            if (x->sign() == ZERO || old_y_sign == NEGATIVE) {
                change_magnitude_up(x, y);
            } else if (x->sign() == old_y_sign) {
                change_magnitude_down(x, y);
            } else {
                change_magnitude_up(x, y);
            }
            y->assign_sign(old_y_sign);
            
            if (swapped) {
                std::swap(x, y);
                x->negate();
                y->negate();
            }
        } else if (y->sign() != ZERO) {
            y->negate();
            add(x, y);
            y->negate();
        }
}
}
