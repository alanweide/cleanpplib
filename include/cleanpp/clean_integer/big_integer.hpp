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

class big_integer_kernel: public clean_base {
public:
	static const int RADIX = 10;

	virtual void multiply_by_radix(int d) = 0;
	virtual void divide_by_radix(int& d) = 0;
	virtual void negate() = 0;
	virtual integer_sign sign() = 0;

	bool operator==(big_integer_kernel &other);
	
	friend std::ostream& operator<<(std::ostream& out, big_integer_kernel& o);
};

class big_integer: public big_integer_kernel {
private:
	virtual void decrease_magnitude();
	virtual void increase_magnitude();
public:
	virtual void increment();
	virtual void decrement();
	virtual void set_from_int(int n);
	
	friend void add(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y);
	friend void subtract(std::unique_ptr<big_integer> &x, std::unique_ptr<big_integer> &y);

};
}

#endif /* big_integer_hpp */
