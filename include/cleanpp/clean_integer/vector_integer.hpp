//
//  vector_integer.hpp
//  Cleanpp
//
//  Created by Alan Weide on 2/10/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef nn_integer_hpp
#define nn_integer_hpp

#include <stdio.h>
#include "big_integer.hpp"

#include <clean_nn/stack_nn.hpp>

namespace cleanpp {
class vector_integer: public big_integer {
public:
	vector_integer(int n = 0);
	
	vector_integer(vector_integer const &other) = delete;
	vector_integer(vector_integer&& other);
	
	vector_integer& operator=(vector_integer const &other) = delete;
	vector_integer& operator=(vector_integer&& other);

	void clear() override;
	void multiply_by_radix(int d) override;
	void divide_by_radix(int &d) override;
	void negate() override;
	integer_sign sign() const override;

private:
	stack_nn n_;
	enum integer_sign sign_;
};
}

#endif /* nn_integer_hpp */
