//
//  template_nn.hpp
//  Cleanpp
//
//  Created by Alan Weide on 7/23/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef template_nn_hpp
#define template_nn_hpp

#include <stdio.h>
#include <clean_base.hpp>
//#include <clean_nn/bounded_nn.hpp>
//#include <clean_nn/stack_nn.hpp>

namespace cleanpp {

template <class I>
class t_natural_number_kernel: public clean_base {
private:
	std::unique_ptr<natural_number_kernel> rep_;
public:
	/*
	 type NATURAL is integer
	 exemplar   n
	 constraint n >= 0
	 
	 natural_number_kernel is modeled by NATURAL
	 */
	
	static const int RADIX = 10;
	
	t_natural_number_kernel(long n = 0) {
		rep_ = std::make_unique<I>(n);
	}
	
	t_natural_number_kernel(const t_natural_number_kernel<I>& other) = delete;
	template<class I2>
	t_natural_number_kernel(t_natural_number_kernel<I2>&& other): rep_(std::move(other.rep_)) {
		other.clear();
	}
	
	t_natural_number_kernel<I>& operator=(const t_natural_number_kernel<I>& other) = delete;
	template<class I2>
	t_natural_number_kernel<I>& operator=(t_natural_number_kernel<I2>&& other) {
		return this->rep_ = std::move(other->rep_);
	}
	
	void clear() override {
		this->rep_->clear();
	}
	
	/*
	 ensures is_zero = (this = 0)
	 */
	virtual bool is_zero() const {
		return this->rep_->is_zero();
	}
	
	/*
	 updates  this
	 requires 0 <= d and d < RADIX
	 ensures  this = #this * RADIX + d
	 */
	virtual void multiply_by_radix(int d) {
		this->rep_->multiply_by_radix(d);
	}
	
	/*
	 updates  this
	 ensures  #this = this * RADIX + d and
	 0 <= d and d < RADIX
	 */
	virtual void divide_by_radix(int &d) {
		this->rep_->divide_by_radix(d);
	}
	
	/*
	 ensures `==` = (this = other)
	 */
	template<class I2>
	bool operator==(t_natural_number_kernel<I2> &other) {
		return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, t_natural_number_kernel<I>& o) {
		return out << *(o.rep_);
	}
};

template<class I>
class t_natural_number_secondary: public t_natural_number_kernel<I> {
private:
//	std::unique_ptr<natural_number_secondary> rep_;
public:
	
    t_natural_number_secondary(long n = 0): t_natural_number_kernel<I>(n) {}

	t_natural_number_secondary(const t_natural_number_secondary<I>& other) = delete;
	template<class I2>
	t_natural_number_secondary(t_natural_number_secondary<I2>&& other): t_natural_number_kernel<I>(other) {
		other.clear();
	}

	t_natural_number_secondary<I>& operator=(const t_natural_number_secondary<I>& other) = delete;
	template<class I2>
	t_natural_number_secondary<I>& operator=(t_natural_number_secondary<I2>&& other) {
		return this->rep_ = std::move(other->rep_);
	}
	
	/*
	 updates this
	 ensures this = #this + 1
	 */
	virtual void increment() {
        int d = 0;
        this->divide_by_radix(d);
        d++;
        if (d == t_natural_number_kernel<I>::RADIX) {
            d -= t_natural_number_kernel<I>::RADIX;;
            this->increment();
        }
        this->multiply_by_radix(d);
	}
	
	/*
	 updates  this
	 requires this > 0
	 ensures  this = #this - 1
	 */
	virtual void decrement() {
        assert(!this->is_zero());
        int d = 0;
        this->divide_by_radix(d);
        d--;
        if (d < 0) {
            d += t_natural_number_kernel<I>::RADIX;
            decrement();
        }
        this->multiply_by_radix(d);
	}
	
	/*
	 replaces this
	 requires n >= 0
	 ensures  this = n
	 */
	virtual void set_from_long(long n) {
        assert(n >= 0);
        if (n == 0) {
          this->clear();
        } else {
            long nLeft = n / t_natural_number_kernel<I>::RADIX;
            this->set_from_long(nLeft);
            this->multiply_by_radix(n % t_natural_number_kernel<I>::RADIX);
        }
	}
	
	/*
	 updates x
	 ensures x = #x + y
	 */
	template<class I2>
	friend t_natural_number_kernel<I> add(t_natural_number_secondary<I> x, t_natural_number_secondary<I2> &y) {
        return add(x.rep_, y.rep_);
	}
	
	/*
	 updates  x
	 requires x >= y
	 ensures  x = #x - y
	 */
	template<class I2>
	friend t_natural_number_secondary<I> subtract(t_natural_number_secondary<I> x, t_natural_number_secondary<I2> &y){
        return subtract(x.rep_, y.rep_);
	}
};

//template class t_natural_number_kernel<bounded_nn>;
//template class t_natural_number_kernel<stack_nn>;
//
//template class t_natural_number_secondary<bounded_nn>;
//template class t_natural_number_secondary<stack_nn>;

}

#endif /* template_nn_hpp */
