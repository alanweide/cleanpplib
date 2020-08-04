////
////  template_nn.cpp
////  Cleanpp
////
////  Created by Alan Weide on 8/3/20.
////  Copyright © 2020 Alan Weide. All rights reserved.
////
//
//#include <stdio.h>
//
//#include <template_nn/template_nn.hpp>
//
//namespace cleanpp {
//
//template<class I>
//t_natural_number_kernel<I>::t_natural_number_kernel(long n) {
//	rep_ = std::make_unique<I>(n);
//}
//
//template<class I>
//template<class I2>
//t_natural_number_kernel<I>::t_natural_number_kernel(t_natural_number_kernel<I2>&& other): rep_(std::move(other.rep_)) {
//	other.clear();
//}
//
//template<class I>
//template<class I2>
//t_natural_number_kernel<I>::t_natural_number_kernel<I>& operator=(t_natural_number_kernel<I2>&& other) {
//	if (&other == this) {
//		return *this;
//	}
//
//	rep_ = other.rep_;
//	other.clear();
//	return *this;
//}
//
//template<class I>
//t_natural_number_kernel<I>::void clear() override {
//	this->rep_->clear();
//}
//
//template<class I>
//t_natural_number_kernel<I>::virtual bool is_zero() const {
//	return this->rep_->is_zero();
//}
//
//template<class I>
//t_natural_number_kernel<I>::virtual void multiply_by_radix(int d) {
//	this->rep_->multiply_by_radix(d);
//}
//
//template<class I>
//t_natural_number_kernel<I>::virtual void divide_by_radix(int &d) {
//	this->rep_->divide_by_radix(d);
//}
//
//template<class I>
//template<class I2>
//t_natural_number_kernel<I>::bool operator==(t_natural_number_kernel<I2> &other) {
//	return *this->rep_ == *other.rep_;
//}
//
//}
