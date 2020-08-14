//
//  template_integer.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/13/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef template_integer_h
#define template_integer_h

#include <clean_integer/big_integer.hpp>

namespace cleanpp {

template<typename I>
class t_big_integer_kernel;

template<typename I>
class t_big_integer;

template<typename I>
class t_big_integer_kernel: public clean_base {
private:
    std::unique_ptr<I> rep_;
public:
    /*
     big_integer_kernel is modeled by integer
     */
    // The "base" of the number
    static const int RADIX = 10;

    t_big_integer_kernel() {
        rep_ = std::make_unique<I>();
    }
    
    t_big_integer_kernel(const t_big_integer_kernel<I> &other) = delete;
    t_big_integer_kernel(t_big_integer_kernel<I>&& other): rep_(std::move(other.rep_)) {
        other.rep_ = std::make_unique<I>();
    }
    
    t_big_integer_kernel<I>& operator=(const t_big_integer_kernel<I>& other) = delete;
    t_big_integer_kernel<I>& operator=(t_big_integer_kernel<I>&& other) {
        if (&other == this) {
            return *this;
        }
        rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<I>();
        return *this;
    }
    
    void clear() override{
        if (!this->rep_) {
            this->rep_ = std::make_unique<I>();
        } else {
            this->rep_->clear();
        }
    }

    /*
     updates  this
     requires 0 <= d and d < 10
     ensures  |this| = |#this| * RADIX + d and
              this < 0 iff #this < 0
     */
    void multiply_by_radix(int d) {
        rep_->multiply_by_radix(d);
    }

    /*
     updates  this
     replaces d
     ensures  |#this| = |this| * RADIX + d and
              0 <= d and d < 10 and
              this < 0 iff #this < 0
     */
    int divide_by_radix() {
        int d;
        rep_->divide_by_radix(d);
        return d;
    }

    /*
     updates this
     ensures this = -#this
     */
    void negate() {
        rep_->negate();
    }
    
    /*
     ensures  this < 0 ==> sign = NEGATIVE and
              this = 0 ==> sign = ZERO and
              this > 0 ==> sign = POSITIVE
     */
    integer_sign sign() const {
        return rep_->sign();
    }
    
    /*
     ensures `==` = (this = other)
     */
    bool operator==(t_big_integer_kernel<I> &other) {
        return *this->rep_ == *other.rep_;
    }
    
    friend std::ostream& operator<<(std::ostream& out, t_big_integer_kernel<I>& o) {
        return out << *o.rep_;
    }
};

template<typename I>
class t_big_integer: public big_integer_kernel {
private:
    
    friend int compare_magnitude(t_big_integer<I> &x, t_big_integer<I> &y) {
        integer_sign x_sign = x.abs();
        integer_sign y_sign = y.abs();
        int comp = compare(x, y);
        x.assign_sign(x_sign);
        y.assign_sign(y_sign);
        return comp;
    }
    
    /*
     updates this
     ensures |this| = |#this| + 1 and
             this < 0 iff #this < 0
     */
    void increase_magnitude() {
        integer_sign sign = this->abs();
        
        int d = this->divide_by_radix();
        d++;
        if (d == big_integer::RADIX) {
            d -= big_integer::RADIX;
            this->increase_magnitude();
        }
        this->multiply_by_radix(d);
        
        this->assign_sign(sign);
    }

    /*
     updates  this
     requires this != 0
     ensures  |this| = |#this| - 1 and
              this < 0 iff #this < 0
     */
    void decrease_magnitude() {
        assert(sign() != ZERO);
        
        integer_sign sign = this->abs();
        
        int d = this->divide_by_radix();
        d--;
        if (d < 0) {
            d += big_integer::RADIX;
            this->decrease_magnitude();
        }
        this->multiply_by_radix(d);
        
        this->assign_sign(sign);
    }
    
    /*
     updates  x
     requires (x > 0 ==> y >= 0) and (x < 0 ==> y <= 0)
     ensures  |x| = |#x| + |y| and (x >= 0 iff #x >= 0)
     */
    friend t_big_integer<I> combine_same(t_big_integer<I>&& x, t_big_integer<I> &y) {
        assert(x.sign() == y.sign() || x.sign() == ZERO || y.sign() == ZERO);

        integer_sign x_sign = x.abs(), y_sign = y.abs();

        int x_low = x.divide_by_radix();
        int y_low = y.divide_by_radix();
        if (y.sign() != ZERO) {
            x = combine_same(std::move(x), y);
        }
        x_low += y_low;
        if (x_low >= t_big_integer::RADIX) {
            x_low -= t_big_integer::RADIX;
            x.increase_magnitude();
        }
        x.multiply_by_radix(x_low);
        y.multiply_by_radix(y_low);

        integer_sign new_x_sign = (x_sign == 0 ? y_sign : x_sign);
        x.assign_sign(new_x_sign);
        
        y.assign_sign(y_sign);
        
        return x;
    }

    
    /*
     updates  x
     requires (x > 0 ==> y <= 0) and (x < 0 ==> y >= 0)
     ensures  |x| = |#x| - |y| and (x >= 0 iff #x >= y)
     */
    friend t_big_integer<I> combine_different(t_big_integer<I>&& x, t_big_integer<I> &y) {
        assert(x.sign() != y.sign() || x.sign() == ZERO);

        int mag_comp = compare_magnitude(x, y);
        if (mag_comp > 0) {
            x = remove(std::move(x), y);
        } else if (mag_comp < 0) {
            t_big_integer<I> tmp = std::move(x);
            x = y.clone();
            x = remove(std::move(x), tmp);
        } else {
            x.clear();
        }
        
        return x;
    }
    
    /*
     updates  x
     requires |x| > |y|
     ensures  |x| = |#x| - |y| and (x >= 0 iff #x >= 0)
     */
    friend t_big_integer<I> remove(t_big_integer<I>&& x, t_big_integer<I> &y) {
        assert(compare_magnitude(x, y) > 0);
        
        integer_sign x_sign = x.abs(), y_sign = y.abs();

        int x_low = x.divide_by_radix();
        int y_low = y->divide_by_radix();
        if (y.sign() != ZERO) {
            x = remove(std::move(x), y);
        }
        x_low -= y_low;
        if (x_low < 0) {
            x_low += big_integer::RADIX;
            x.decrease_magnitude();
        }
        x.multiply_by_radix(x_low);
        y.multiply_by_radix(y_low);
        
        x.assign_sign(x_sign);
        y.assign_sign(y_sign);
        
        return x;
    }

public:
    
    t_big_integer(long n = 0): t_big_integer_kernel<I>(n) {}

    t_big_integer(const t_big_integer<I>& other) = delete;
    t_big_integer(t_big_integer<I>&& other): t_big_integer_kernel<I>(std::move(other)) {
        other.rep_ = std::make_unique<I>();
    }

    t_big_integer<I>& operator=(const t_big_integer<I>& other) = delete;
    t_big_integer<I>& operator=(t_big_integer<I>&& other) {
        if (&other == this) {
            return *this;
        }
        this->rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<I>();
        return *this;
    }

    /*
     updates this
     ensures this = #this + 1
     */
    void increment() {
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

    /*
     updates this
     ensures this = #this - 1
     */
    void decrement() {
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
    
    /*
     replaces this
     ensures  this = n
     */
    void set_from_int(int n) {
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

    /*
     requires 0 <= d and d < 10
     ensures  this = |#this| and abs = [POSITIVE, ZERO, or NEGATIVE as this > 0, = 0, or < 0]
     */
    integer_sign abs() {
        integer_sign sign = this->sign();
        if (sign == NEGATIVE) {
            negate();
        }
        return sign;
    }
    
    /*
     updates  this
     ensures  sign = NEGATIVE ==> this = -|#this| and
              sign = ZERO     ==> this = #this and
              sign = POSITIVE ==> this = |#this|
     */
    void assign_sign(integer_sign sign){
        if (this->sign() == -sign) {
            this->negate();
        }
    }
    
    /*
     ensures clone = this
     */
    t_big_integer<I> clone() {
        t_big_integer<I> clone;
        if (this->sign() == ZERO) {
            clone = this->new_instance();
        } else {
            integer_sign this_sign = this->abs();
            
            int d;
            this->divide_by_radix(d);
            
            clone = this->clone();
            
            clone.multiply_by_radix(d);
            this->multiply_by_radix(d);
            
            clone.assign_sign(this_sign);
            this->assign_sign(this_sign);
        }
        return clone;
    }

    /*
     updates  x
     ensures  x = #x + y
     */
    friend t_big_integer<I> add(t_big_integer<I>&& x, t_big_integer<I> &y) {

        if (x.sign() == ZERO || x.sign() == y->sign()) {
            return combine_same(std::move(x), y);
        } else {
            return combine_different(std::move(x), y);
        }
    }
    
    /*
     updates x
     ensures x = #x - y
     */
    friend t_big_integer<I> subtract(t_big_integer<I>&& x, t_big_integer<I> &y){
        y.negate();
        t_big_integer<I> sum = add(x, y);
        y.negate();
        
        return sum;
    }

    /*
     ensures compare > 0 ==> x > y and
             compare = 0 ==> x = y and
             compare < 0 ==> x < y
     */
    friend int compare(t_big_integer<I> &x, t_big_integer<I> &y) {
        integer_sign x_sign = x.sign(), y_sign = y.sign();
        if (x_sign > y_sign) {
            return 1;
        } else if (x_sign < y_sign) {
            return -1;
        } else if (x_sign == ZERO && y_sign == ZERO) {
            return 0;
        } else {
            x_sign = x.abs();
            y_sign = y.abs();
            int x_low = x.divide_by_radix();
            int y_low = y->divide_by_radix();
            int comp = compare(x, y);
            if (comp == 0) {
                comp = x_low - y_low;
            }
            x.multiply_by_radix(x_low);
            y.multiply_by_radix(y_low);
            
            x.assign_sign(x_sign);
            y.assign_sign(y_sign);
            
            return comp * x_sign;
        }
    }
};

}

#endif /* template_integer_h */
