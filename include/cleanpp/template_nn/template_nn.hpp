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
#include "clean_base.hpp"
#include "natural_number.hpp"

namespace cleanpp {

template<class I>
class t_natural_number;

template <class I>
class t_natural_number_kernel: public clean_base {
protected:
    std::unique_ptr<natural_number_kernel> rep_;
public:
	/*
	 type NATURAL is integer
	 exemplar   n
	 constraint n >= 0
	 
	 natural_number_kernel is modeled by NATURAL
	 */
	static const int RADIX = 10;
	
	t_natural_number_kernel(long n = 0): rep_(std::make_unique<I>(n)) {
        static_assert(std::is_base_of<natural_number_kernel, I>::value,
                      "Template parameter I must derive from cleanpp::natural_number_kernel");
	}
	
	t_natural_number_kernel(const t_natural_number_kernel<I>& other) = delete;
	t_natural_number_kernel(t_natural_number_kernel<I>&& other): rep_(std::move(other.rep_)) {
        static_assert(std::is_base_of<natural_number_kernel, I>::value,
                      "Template parameter I must derive from cleanpp::natural_number_kernel");
		other.rep_ = std::make_unique<I>();
	}
	
	t_natural_number_kernel<I>& operator=(const t_natural_number_kernel<I>& other) = delete;
	t_natural_number_kernel<I>& operator=(t_natural_number_kernel<I>&& other) {
		if (&other == this) {
			return *this;
		}
		rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<I>();
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
     ensures new_instance = 0
     */
    t_natural_number_kernel<I> new_instance() const {
        return t_natural_number_kernel<I>();
    }
	
	/*
	 ensures `==` = (this = other)
	 */
    bool operator==(t_natural_number_kernel<I> &other)	{
        return *this->rep_ == *other.rep_;
	}
	
	friend std::ostream& operator<<(std::ostream& out, t_natural_number_kernel<I>& o) {
		return out << *(o.rep_);
	}
	
	friend class t_natural_number<I>;
};

template<class I>
class t_natural_number: public t_natural_number_kernel<I> {
public:
	
	t_natural_number(long n = 0): t_natural_number_kernel<I>(n) {
		static_assert(std::is_base_of<natural_number_secondary, I>::value, "Template parameter I must derive from cleanpp::natural_number_secondary");
	}
	
	t_natural_number(const t_natural_number<I>& other) = delete;
	t_natural_number(t_natural_number<I>&& other): t_natural_number_kernel<I>(std::forward<t_natural_number_kernel<I>&&>(other)) {
		static_assert(std::is_base_of<natural_number_secondary, I>::value, "Template parameter I must derive from cleanpp::natural_number_secondary");
		other.rep_ = std::make_unique<I>();
	}
	
	t_natural_number<I>& operator=(const t_natural_number<I>& other) = delete;
	t_natural_number<I>& operator=(t_natural_number<I>&& other) {
		if (&other == this) {
			return *this;
		}
		this->rep_ = std::move(other.rep_);
		other.rep_ = std::make_unique<I>();
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
     ensures new_instance = 0
     */
    t_natural_number<I> new_instance() const {
        return t_natural_number<I>();
    }
    
	/*
	 ensures add = #x + y
	 */
	template<class I2>
	friend t_natural_number<I> add(t_natural_number<I>&& x, t_natural_number<I2> &y) {
        t_natural_number<I> sum(std::forward<t_natural_number<I>>(x));
        
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
	template<class I2>
	friend t_natural_number<I> subtract(t_natural_number<I>&& x, t_natural_number<I2> &y) {
		t_natural_number<I> diff(std::forward<t_natural_number<I>>(x));
		
		std::unique_ptr<natural_number_secondary> diff_casted(static_cast<natural_number_secondary*>(diff.rep_.release()));
		std::unique_ptr<natural_number_secondary> y_casted(static_cast<natural_number_secondary*>(y.rep_.release()));
		
        diff_casted = subtract(std::move(diff_casted), y_casted);
		
        y.rep_ = std::move(y_casted);
		diff.rep_ = std::move(diff_casted);
		
		return diff;
	}
};

}

#endif /* template_nn_hpp */
