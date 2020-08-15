//
//  vector_integer.cpp
//  Cleanpp
//
//  Created by Alan Weide on 2/10/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <clean_integer/vector_integer.hpp>

namespace cleanpp {
vector_integer::vector_integer(int n) {
    set_from_long(n);
}

vector_integer::vector_integer(vector_integer &&other): rep_(std::move(other.rep_)), sign_(other.sign_) {
	other.clear();
}

vector_integer& vector_integer::operator=(vector_integer &&other) {
	if (&other == this) {
		return *this;
	}
	rep_ = std::move(other.rep_);
	sign_ = std::move(other.sign_);
	other.clear();
	return *this;
}

// big_integer_kernel
void vector_integer::clear() {
	rep_.clear();
	sign_ = ZERO;
}

int vector_integer::divide_by_radix() {
	int d;
	if (!rep_.empty()) {
        d = rep_.back();
        rep_.pop_back();
    } else {
        d = 0;
    }
    if (rep_.empty()) {
        sign_ = ZERO;
    }
    assert (0 <= d && d < RADIX);
	return d;
}

void vector_integer::multiply_by_radix(int d) {
	assert (0 <= d && d < RADIX);
    if (0 < d && rep_.empty()) {
        sign_ = POSITIVE;
    }
    if (!rep_.empty() || d != 0) {
        rep_.push_back(d);
    }
}

integer_sign vector_integer::sign() const {
	return sign_;
}

void vector_integer::negate() {
	if (sign_ == POSITIVE) {
		sign_ = NEGATIVE;
	} else if (sign_ == NEGATIVE) {
		sign_ = POSITIVE;
	}
}

std::unique_ptr<big_integer> vector_integer::new_instance() const {
    return std::make_unique<vector_integer>();
}

}
