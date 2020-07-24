//
//  template_nn.cpp
//  Cleanpp
//
//  Created by Alan Weide on 7/23/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <template_nn.hpp>

namespace cleanpp {

template<class I>
template_nn_kernel<I>::template_nn_kernel() {
    val_ = std::make_unique<I>();
}

template<class I>
template_nn_kernel<I>::template_nn_kernel(template_nn_kernel<I>&& other): val_(std::move(other.val_)) {
	other.clear();
}

template<class I>
void template_nn_kernel<I>::clear() {
	this->val_->clear();
}

template<class I>
bool template_nn_kernel<I>::is_zero() const {
	return this->val_->is_zero();
}

template<class I>
void template_nn_kernel<I>::multiply_by_radix(int d) {
	this->val_->multiply_by_radix(d);
}

template<class I>
void template_nn_kernel<I>::divide_by_radix(int &d) {
	this->val_->divide_by_radix(d);
}

template<class I>
bool template_nn_kernel<I>::operator==(template_nn_kernel<I> &other) {
	return this->val_ == other.val_;
}

template<class I>
std::ostream& operator<<(std::ostream& out, template_nn_kernel<I>& o) {
	return out << o.val_;
}
}
