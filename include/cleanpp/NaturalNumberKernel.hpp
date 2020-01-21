//
//  NaturalNumberKernel.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef NaturalNumberKernel_hpp
#define NaturalNumberKernel_hpp

#include <stdio.h>
#include "CleanBase.hpp"

namespace cleanpp {
class natural_number_kernel: public clean_base<void> {
public:
    static const int RADIX = 10;
    virtual bool is_zero() = 0;
    virtual void multiply_by_radix(int digit) = 0;
    virtual void divide_by_radix(int &digit) = 0;
};
}

#endif /* NaturalNumberKernel_hpp */
