//
//  BoundedNN.cpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <stdio.h>
#include<BoundedNN.hpp>

namespace cleanpp {
bounded_nn::bounded_nn(): n(0) {};

bounded_nn::bounded_nn(bounded_nn&& other): n(std::move(other.n)) {
    other.clear();
}

bounded_nn& bounded_nn::operator=(bounded_nn&& other) {
    if (&other == this) {
        return *this;
    }
    
    n = other.n;
    other.clear();
    return *this;
}
void bounded_nn::clear() {
    this->n = 0;
}
bool bounded_nn::is_zero() {
    return this->n == 0;
}
void bounded_nn::multiply_by_radix(int d) {
    this->n *= RADIX;
    this->n += d;
}
void bounded_nn::divide_by_radix(int &d) {
    d = this->n % RADIX;
    this->n /= RADIX;
}

void bounded_nn::increment() {
    this->n++;
}

void bounded_nn::decrement() {
    this->n--;
}

void bounded_nn::set_from_int(int n) {
    this->n = n;
}

std::ostream& bounded_nn::print(std::ostream& out) {
    return out << this->n;
}

}
