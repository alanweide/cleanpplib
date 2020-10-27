//
//  bounded_nn.cpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <memory>
#include <stdio.h>
#include <bounded_nn.hpp>


namespace cleanpp {
bounded_nn::bounded_nn(long n): n_(n) {};

bounded_nn::bounded_nn(bounded_nn&& other): n_(std::move(other.n_)) {
    other.clear();
}

bounded_nn::~bounded_nn() {
	n_ = 0;
}

bounded_nn& bounded_nn::operator=(bounded_nn&& other) {
    if (&other == this) {
        return *this;
    }
    
    n_ = other.n_;
    other.clear();
    return *this;
}

bool bounded_nn::operator==(const bounded_nn &other) {
    return this->n_ == other.n_;
}

void bounded_nn::clear() {
    n_ = 0;
}
bool bounded_nn::is_zero() const {
    return n_ == 0;
}
void bounded_nn::multiply_by_radix(int d) {
    n_ *= RADIX;
    n_ += d;
}
int bounded_nn::divide_by_radix() {
    int d = n_ % RADIX;
    n_ /= RADIX;
	return d;
}

std::unique_ptr<clean_natural_number_kernel> bounded_nn::new_instance() {
    return std::make_unique<bounded_nn>();
}

void bounded_nn::increment() {
    this->n_++;
}

void bounded_nn::decrement() {
    this->n_--;
}

void bounded_nn::set_from_long(long n) {
    this->n_ = n;
}

void bounded_nn::divide_by_two() {
    this->n_ /= 2;
}

}
