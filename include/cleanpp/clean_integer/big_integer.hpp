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

class big_integer_kernel: public clean_base {
public:
	enum sign {
		NEGATIVE, ZERO, POSITIVE
	};
	static const int RADIX = 10;

	virtual void multiply_by_radix(int d) = 0;
	virtual void divide_by_radix(int& d) = 0;
	virtual void negate() = 0;
	virtual sign sign() = 0;

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
	
//	friend void add(big_integer &x, big_integer &y);
//	friend void subtract(big_integer &x, big_integer &y);

};
}

#endif /* big_integer_hpp */
