//
//  big_integer.hpp
//  Cleanpp
//
//  Created by Alan Weide on 2/10/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef big_integer_hpp
#define big_integer_hpp

#include <stdio.h>

#include <clean_base.hpp>

namespace cleanpp {

enum integer_sign {
	NEGATIVE = -1, ZERO = 0, POSITIVE = 1
};

class big_integer_kernel;
class big_integer;

class big_integer_kernel: public clean_base {
    /*
     big_integer_kernel is modeled by integer
     */
public:
    // The "base" of the number
	static const int RADIX = 10;

    /*
     updates  this
     requires 0 <= d and d < 10
     ensures  |this| = |#this| * RADIX + d and
              this < 0 iff #this < 0
     */
	virtual void multiply_by_radix(int d) = 0;

    /*
     updates  this
     ensures  |#this| = |this| * RADIX + divide_by_radix and
              0 <= divide_by_radix and divide_by_radix < 10 and
              this < 0 iff #this < 0
     */
    virtual int divide_by_radix() = 0;

    /*
     updates this
     ensures this = -#this
     */
    virtual void negate() = 0;
	
    /*
     ensures  this < 0 ==> sign = NEGATIVE and
              this = 0 ==> sign = ZERO and
              this > 0 ==> sign = POSITIVE
     */
    virtual integer_sign sign() const = 0;
    
    /*
     ensures new_instance = 0
     */
    virtual std::unique_ptr<big_integer> new_instance() const = 0;

    /*
     ensures `==` = (this = other)
     */
	bool operator==(big_integer_kernel &other);
	
	friend std::ostream& operator<<(std::ostream& out, big_integer_kernel& o);
};

class big_integer: public big_integer_kernel {
private:
    
    /*
     updates this
     ensures |this| = |#this| + 1 and
             this < 0 iff #this < 0
     */
    virtual void increase_magnitude();

    /*
     updates  this
     requires this != 0
     ensures  |this| = |#this| - 1 and
              this < 0 iff #this < 0
     */
    virtual void decrease_magnitude();
    
    /*
     updates  x
     requires (x > 0 ==> y >= 0) and (x < 0 ==> y <= 0)
     ensures  |x| = |#x| + |y| and (x >= 0 iff #x >= 0)
     */
    friend std::unique_ptr<big_integer> combine_same(std::unique_ptr<big_integer> &&x, std::unique_ptr<big_integer> &y);
    
    /*
     updates  x
     requires (x > 0 ==> y <= 0) and (x < 0 ==> y >= 0)
     ensures  |x| = |#x| - |y| and (x >= 0 iff #x >= y)
     */
	friend std::unique_ptr<big_integer> combine_different(std::unique_ptr<big_integer> &&x, std::unique_ptr<big_integer> &y);
    
    /*
     updates  x
     requires |x| > |y|
     ensures  |x| = |#x| - |y| and (x >= 0 iff #x >= 0)
     */
    friend std::unique_ptr<big_integer> remove(std::unique_ptr<big_integer> &&x, std::unique_ptr<big_integer> &y);

public:
    
    /*
     updates this
     ensures this = #this + 1
     */
	virtual void increment();

    /*
     updates this
     ensures this = #this - 1
     */
    virtual void decrement();
	
    /*
     replaces this
     ensures  this = n
     */
    virtual void set_from_long(long n);
    
    /*
     requires 0 <= d and d < 10
     ensures  this = |#this|
     */
    virtual integer_sign abs();
    
    /*
     updates  this
     ensures  sign = NEGATIVE ==> this = -|#this| and
              sign = ZERO     ==> this = #this and
              sign = POSITIVE ==> this = |#this|
     */
    virtual void assign_sign(integer_sign sign);
    
    /*
     ensures clone = this
     */
    virtual std::unique_ptr<big_integer> clone();

    /*
     updates  x
     ensures  x = #x + y
     */
    friend std::unique_ptr<big_integer> add(std::unique_ptr<big_integer> &&x, std::unique_ptr<big_integer> &y);
    
    /*
     updates x
     ensures x = #x - y
     */
	friend std::unique_ptr<big_integer> subtract(std::unique_ptr<big_integer> &&x, std::unique_ptr<big_integer> &y);

    /*
     ensures compare > 0 ==> x > y and
             compare = 0 ==> x = y and
             compare < 0 ==> x < y
     */
    friend int compare(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y);
	
	template<typename I>
	friend class t_big_integer;
};
}

#endif /* big_integer_hpp */
