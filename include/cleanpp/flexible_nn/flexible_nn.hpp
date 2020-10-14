//
//  flexible_nn.hpp
//  Cleanpp
//
//  Created by Alan Weide on 7/23/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef flex_nn_hpp
#define flex_nn_hpp

#include <stdio.h>
#include "clean_base.hpp"
#include "natural_number.hpp"
#include "stack_nn.hpp"

namespace cleanpp {

class flex_natural_number_kernel: public clean_base {
protected:
    typedef stack_nn _flex_nn_def_t;
    
    std::unique_ptr<natural_number_kernel> rep_;
public:
	/*
	 type NATURAL is integer
	 exemplar   n
	 constraint n >= 0
	 
	 natural_number_kernel is modeled by NATURAL
	 */
	static const int RADIX = 10;
	
    flex_natural_number_kernel(long n = 0): rep_(std::make_unique<_flex_nn_def_t>(n)) {}
    
    template<typename I>
    flex_natural_number_kernel(__attribute__((unused)) const I& impl, long n = 0): rep_(std::make_unique<I>(n)) {
        static_assert(std::is_base_of<natural_number_kernel, I>::value,
                      "Type of impl must derive from cleanpp::natural_number_kernel");
	}
	
	flex_natural_number_kernel(const flex_natural_number_kernel& other) = delete;
	flex_natural_number_kernel(flex_natural_number_kernel&& other): rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<_flex_nn_def_t>();
	}
	
	flex_natural_number_kernel& operator=(const flex_natural_number_kernel& other) = delete;
    flex_natural_number_kernel& operator=(flex_natural_number_kernel&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<_flex_nn_def_t>();
		return *this;
	}
	
	void clear() override{
		this->rep_->clear();
	}
	
	/*
	 ensures is_zero = (this = 0)
	 */
	bool is_zero() const{
		return this->rep_->is_zero();
	}
	
	/*
	 updates  this
	 requires 0 <= d and d < RADIX
	 ensures  this = #this * RADIX + d
	 */
	void multiply_by_radix(int&& d){
		this->rep_->multiply_by_radix(d);
	}
	
	/*
	 updates  this
	 ensures  #this = this * RADIX + d and
	 0 <= d and d < RADIX
	 */
	int divide_by_radix() {
		return this->rep_->divide_by_radix();
	}
    
	/*
	 ensures `==` = (this = other)
	 */
    bool operator==(flex_natural_number_kernel &other)	{
        return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, flex_natural_number_kernel& o) {
		return out << *(o.rep_);
	}
	
	friend class flex_natural_number;
};

class flex_natural_number: public flex_natural_number_kernel {
public:
	
    flex_natural_number(long n = 0): flex_natural_number_kernel(n) {}
    
    template<class I>
	flex_natural_number(__attribute__((unused)) const I& impl, long n = 0): flex_natural_number_kernel(impl, n) {
		static_assert(std::is_base_of<natural_number_secondary, I>::value, "Template parameter I must derive from cleanpp::natural_number_secondary");
	}
	
	flex_natural_number(const flex_natural_number& other) = delete;
	flex_natural_number(flex_natural_number&& other): flex_natural_number_kernel(std::forward<flex_natural_number_kernel>(other)) {
		other.rep_ = std::make_unique<_flex_nn_def_t>();
	}
	
	flex_natural_number& operator=(const flex_natural_number& other) = delete;
	flex_natural_number& operator=(flex_natural_number&& other) {
		if (&other == this) {
			return *this;
		}
		this->rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<_flex_nn_def_t>();
		return *this;
	}
	
	/*
	 updates this
	 ensures this = #this + 1
	 */
	void increment() {
		std::unique_ptr<natural_number_secondary> casted(static_cast<natural_number_secondary*>(this->rep_.release()));
		
        casted->increment();
		
        this->rep_ = std::move(casted);
	}
	
	/*
	 updates  this
	 requires this > 0
	 ensures  this = #this - 1
	 */
	void decrement() {
		assert(!this->is_zero());
		std::unique_ptr<natural_number_secondary> casted(static_cast<natural_number_secondary*>(this->rep_.release()));
		
        casted->decrement();
		
        this->rep_ = std::move(casted);
	}
	
	/*
	 replaces this
	 requires n >= 0
	 ensures  this = n
	 */
	void set_from_long(long n) {
		assert(n >= 0);
		std::unique_ptr<natural_number_secondary> casted(static_cast<natural_number_secondary*>(this->rep_.release()));
		
        casted->set_from_long(n);
		
        this->rep_ = std::move(casted);
	}
	    
	/*
	 ensures add = #x + y
	 */
	friend flex_natural_number add(flex_natural_number&& x, flex_natural_number &y) {
        flex_natural_number sum(std::forward<flex_natural_number>(x));
        
        std::unique_ptr<natural_number_secondary> sum_casted(static_cast<natural_number_secondary*>(sum.rep_.release()));
        std::unique_ptr<natural_number_secondary> y_casted(static_cast<natural_number_secondary*>(y.rep_.release()));
        
        sum_casted = add(std::move(sum_casted), y_casted);
        
        y.rep_ = std::move(y_casted);
        sum.rep_ = std::move(sum_casted);
        
        return sum;
	}
	
	/*
	 requires x >= y
	 ensures  add = #x - y
	 */
	friend flex_natural_number subtract(flex_natural_number&& x, flex_natural_number &y) {
		flex_natural_number diff(std::forward<flex_natural_number>(x));
		
		std::unique_ptr<natural_number_secondary> diff_casted(static_cast<natural_number_secondary*>(diff.rep_.release()));
		std::unique_ptr<natural_number_secondary> y_casted(static_cast<natural_number_secondary*>(y.rep_.release()));
		
        diff_casted = subtract(std::move(diff_casted), y_casted);
		
        y.rep_ = std::move(y_casted);
		diff.rep_ = std::move(diff_casted);
		
		return diff;
	}

    /*
     ensures  add = #x * y
     */
    friend flex_natural_number multiply(flex_natural_number&& x, flex_natural_number &y) {
        flex_natural_number product(std::forward<flex_natural_number>(x));
        
        std::unique_ptr<natural_number_secondary> product_casted(static_cast<natural_number_secondary*>(product.rep_.release()));
        std::unique_ptr<natural_number_secondary> y_casted(static_cast<natural_number_secondary*>(y.rep_.release()));
        
        product_casted = multiply(std::move(product_casted), y_casted);
        
        y.rep_ = std::move(y_casted);
        product.rep_ = std::move(product_casted);
        
        return product;
    }
};

}

#endif /* flex_nn_hpp */
