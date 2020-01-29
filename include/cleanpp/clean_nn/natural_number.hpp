//
//  natural_number.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef natural_number_h
#define natural_number_h

#include "natural_number_kernel.hpp"

namespace cleanpp {
class natural_number: public natural_number_kernel {
public:
    virtual void increment();
    virtual void decrement();
    virtual void set_from_int(int n);
};

void add(std::unique_ptr<natural_number> &x, std::unique_ptr<natural_number> &y);
void subtract(std::unique_ptr<natural_number> &x, std::unique_ptr<natural_number> &y);

}

#endif /* natural_number_h */
