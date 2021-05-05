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
#include <assert.h>
#include <clean_base.hpp>
#include <natural_number.hpp>
#include <nn_impl/nn_impl.hpp>
#include <nn_impl/stack_nn.hpp>

namespace cleanpp {

class natural_number_kernel: public clean_base {
protected:
    typedef stack_nn _flex_nn_def_t;
    
    std::unique_ptr<natural_number_kernel_impl> rep_;
public:
	/**
	 type NATURAL is integer
	 exemplar   n
	 constraint n >= 0
	 
	 natural_number_kernel is modeled by NATURAL
	 */
	static const int RADIX = 10;
	
    natural_number_kernel(long n = 0): rep_(std::make_unique<_flex_nn_def_t>(n)) {}
    
    template<typename I>
    natural_number_kernel(__attribute__((unused)) const I& impl, long n = 0): rep_(std::make_unique<I>(n)) {
        static_assert(std::is_base_of<natural_number_kernel_impl, I>::value,
                      "Type of impl must derive from cleanpp::natural_number_kernel");
	}
	
	natural_number_kernel(const natural_number_kernel& other) = delete;
	natural_number_kernel(natural_number_kernel&& other): rep_(std::move(other.rep_)) {
		other.rep_ = std::make_unique<_flex_nn_def_t>();
	}
	
	natural_number_kernel& operator=(const natural_number_kernel& other) = delete;
    natural_number_kernel& operator=(natural_number_kernel&& other) {
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
	
	/**
	 ensures is_zero = (this = 0)
	 */
	bool is_zero() const{
		return this->rep_->is_zero();
	}
	
	/**
	 updates  this
	 requires 0 <= d and d < RADIX
	 ensures  this = #this * RADIX + d
	 */
	void multiply_by_radix(int&& d){
		this->rep_->multiply_by_radix(d);
	}
	
	/**
	 updates  this
	 ensures  #this = this * RADIX + d and
	 0 <= d and d < RADIX
	 */
	int divide_by_radix() {
		return this->rep_->divide_by_radix();
	}
    
	/**
	 ensures `==` = (this = other)
	 */
    bool operator==(natural_number_kernel &other)	{
        return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, natural_number_kernel& o) {
		return out << *(o.rep_);
	}
	
	friend class flex_natural_number;
};

class natural_number: public natural_number_kernel {
public:
	
    natural_number(long n = 0): natural_number_kernel(n) {}
    
    template<class I>
    natural_number(__attribute__((unused)) const I& impl, long n = 0): natural_number_kernel(impl, n) {
		static_assert(std::is_base_of<natural_number_impl, I>::value, "Template parameter I must derive from cleanpp::natural_number_secondary");
	}
	
    natural_number(const natural_number& other) = delete;
    natural_number(natural_number&& other): natural_number_kernel(std::forward<natural_number_kernel>(other)) {
		other.rep_ = std::make_unique<_flex_nn_def_t>();
	}
	
    natural_number& operator=(const natural_number& other) = delete;
    natural_number& operator=(natural_number&& other) {
		if (&other == this) {
			return *this;
		}
		this->rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<_flex_nn_def_t>();
		return *this;
	}
	
	/**
	 updates this
	 ensures this = #this + 1
	 */
	void increment() {
		std::unique_ptr<natural_number_impl> casted(static_cast<natural_number_impl*>(this->rep_.release()));
		
        casted->increment();
		
        this->rep_ = std::move(casted);
	}
	
	/**
	 updates  this
	 requires this > 0
	 ensures  this = #this - 1
	 */
	void decrement() {
		assert(!this->is_zero());
		std::unique_ptr<natural_number_impl> casted(static_cast<natural_number_impl*>(this->rep_.release()));
		
        casted->decrement();
		
        this->rep_ = std::move(casted);
	}
	
	/**
	 replaces this
	 requires n >= 0
	 ensures  this = n
	 */
	void set_from_long(long n) {
		assert(n >= 0);
		std::unique_ptr<natural_number_impl> casted(static_cast<natural_number_impl*>(this->rep_.release()));
		
        casted->set_from_long(n);
		
        this->rep_ = std::move(casted);
	}
	    
    /**
     updates this
     ensures this = #this / 2
     */
    void divide_by_two() {
        std::unique_ptr<natural_number_impl> casted(static_cast<natural_number_impl*>(this->rep_.release()));
        
        casted->divide_by_two();
        
        this->rep_ = std::move(casted);
    }
    
	/**
	 ensures `==` = (this = other)
	 */
    bool operator==(natural_number &other)	{
        return *this->rep_ == *other.rep_;
	}
	

	/**
	 ensures add = #x + y
	 */
	friend natural_number add(natural_number&& x, natural_number &y) {
        natural_number sum(std::forward<natural_number>(x));
        
        std::unique_ptr<natural_number_impl> sum_casted(static_cast<natural_number_impl*>(sum.rep_.release()));
        std::unique_ptr<natural_number_impl> y_casted(static_cast<natural_number_impl*>(y.rep_.release()));
        
        sum_casted = add(std::move(sum_casted), y_casted);
        
        y.rep_ = std::move(y_casted);
        sum.rep_ = std::move(sum_casted);
        
        return sum;
	}
	
	/**
	 requires x >= y
	 ensures  subtract = #x - y
	 */
	friend natural_number subtract(natural_number&& x, natural_number &y) {
        natural_number diff(std::forward<natural_number>(x));
		
		std::unique_ptr<natural_number_impl> diff_casted(static_cast<natural_number_impl*>(diff.rep_.release()));
		std::unique_ptr<natural_number_impl> y_casted(static_cast<natural_number_impl*>(y.rep_.release()));
		
        diff_casted = subtract(std::move(diff_casted), y_casted);
		
        y.rep_ = std::move(y_casted);
		diff.rep_ = std::move(diff_casted);
		
		return diff;
	}

    /**
     ensures  \f$\mathtt{add} = \mathtt{\#x} \times \mathtt{y}\f$
     */
    friend natural_number multiply(natural_number&& x, natural_number &y) {
        natural_number product(std::forward<natural_number>(x));
        
        std::unique_ptr<natural_number_impl> product_casted(static_cast<natural_number_impl*>(product.rep_.release()));
        std::unique_ptr<natural_number_impl> y_casted(static_cast<natural_number_impl*>(y.rep_.release()));
        
        product_casted = multiply(std::move(product_casted), y_casted);
        
        y.rep_ = std::move(y_casted);
        product.rep_ = std::move(product_casted);
        
        return product;
    }
};

}

#endif /* flex_nn_hpp */
