//
//  natural_number.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef natural_number_h
#define natural_number_h

#include <clean_base.hpp>

namespace cleanpp {

class natural_number_kernel: public clean_base {
public:
    static const int RADIX = 10;
    
    virtual bool is_zero() = 0;
    virtual void multiply_by_radix(int digit) = 0;
    virtual void divide_by_radix(int &digit) = 0;
    
    bool operator==(natural_number_kernel &other);
    
    friend std::ostream& operator<<(std::ostream& out, natural_number_kernel& o);
};

class natural_number: public natural_number_kernel {
public:
    virtual void increment();
    virtual void decrement();
    virtual void set_from_int(int n);
    
    friend void add(std::unique_ptr<natural_number> &x, std::unique_ptr<natural_number> &y);
    friend void subtract(std::unique_ptr<natural_number> &x, std::unique_ptr<natural_number> &y);
};

}

#endif /* natural_number_h */
