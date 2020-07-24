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
#include <clean_nn/bounded_nn.hpp>
#include <clean_nn/stack_nn.hpp>

namespace cleanpp {

template <class I>
class template_nn_kernel: public clean_base {
private:
	std::unique_ptr<I> val_;
public:
	static const int RADIX = 10;
	
    template_nn_kernel();
    
	template_nn_kernel(template_nn_kernel<I> const &other) = delete;
	template_nn_kernel(template_nn_kernel<I>&& other);
	
	template_nn_kernel<I>& operator=(const template_nn_kernel<I>& other) = delete;
	template_nn_kernel<I>& operator=(template_nn_kernel<I>&& other);
	
	virtual void clear() override;
	
	virtual bool is_zero() const;
	
	virtual void multiply_by_radix(int d);
	
	virtual void divide_by_radix(int &d);
	
	bool operator==(template_nn_kernel<I> &other);
	
	friend std::ostream& operator<<(std::ostream& out, template_nn_kernel<I>& o);
};

template class template_nn_kernel<bounded_nn>;
template class template_nn_kernel<stack_nn>;

}

#endif /* template_nn_hpp */
