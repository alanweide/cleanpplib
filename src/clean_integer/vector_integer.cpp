//
//  nn_integer.cpp
//  Cleanpp
//
//  Created by Alan Weide on 2/10/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <clean_integer/nn_integer.hpp>

namespace cleanpp {
nn_integer::nn_integer(int n) {
	if (n < 0) {
		sign_ = NEGATIVE;
		n *= -1;
	} else if (n == 0) {
		sign_ = ZERO;
	} else {
		sign_ = POSITIVE;
	}
	n_ = stack_nn(n);
}

nn_integer::nn_integer(nn_integer &&other): n_(std::move(other.n_)), sign_(other.sign_) {
	other.clear();
}

nn_integer& nn_integer::operator=(nn_integer &&other) {
	if (&other == this) {
		return *this;
	}
	n_ = std::move(other.n_);
	sign_ = std::move(other.sign_);
	other.clear();
	return *this;
}

// big_integer_kernel
void nn_integer::clear() {
	n_.clear();
	sign_ = ZERO;
}

void nn_integer::divide_by_radix(int &d) {
	n_.divide_by_radix(d);
	if (n_.is_zero()) {
		sign_ = ZERO;
	}
	assert (0 <= d && d < RADIX);
}

void nn_integer::multiply_by_radix(int d) {
	assert (0 <= d && d < RADIX);
	if (0 < d && n_.is_zero()) {
		sign_ = POSITIVE;
	}
	n_.multiply_by_radix(d);
}

integer_sign nn_integer::sign() {
	return sign_;
}

void nn_integer::negate() {
	if (sign_ == POSITIVE) {
		sign_ = NEGATIVE;
	} else if (sign_ == NEGATIVE) {
		sign_ = POSITIVE;
	}
}

}
