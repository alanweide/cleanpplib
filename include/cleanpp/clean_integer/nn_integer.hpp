//
//  nn_integer.hpp
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
class nn_integer: public big_integer {
public:
	nn_integer(int n = 0);
	
	nn_integer(nn_integer const &other) = delete;
	nn_integer(nn_integer&& other);
	
	nn_integer& operator=(nn_integer const &other) = delete;
	nn_integer& operator=(nn_integer&& other);

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
