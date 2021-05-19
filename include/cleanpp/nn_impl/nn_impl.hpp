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

namespace cleanpp
{

class natural_number_kernel_impl : public clean_base {
    /*
     type NATURAL is integer
        exemplar   n
        constraint n >= 0

     natural_number_kernel is modeled by NATURAL
     */
    public:
    static const int RADIX = 10;

    /*
     ensures is_zero = (this = 0)
     */
    virtual bool is_zero() const = 0;

    /*
     updates  this
     requires 0 <= d and d < RADIX
     ensures  this = #this * RADIX + d
     */
    virtual void multiply_by_radix(int d) = 0;

    /*
     updates  this
     ensures  #this = this * RADIX + divide_by_radix and
              0 <= divide_by_radix and divide_by_radix < RADIX
     */
    virtual int divide_by_radix() = 0;

    virtual std::unique_ptr<natural_number_kernel_impl> new_instance() = 0;

    /*
     ensures `==` = (this = other)
     */
    virtual bool operator==(natural_number_kernel_impl& other);

    friend std::ostream& operator<<(std::ostream& out, natural_number_kernel_impl& o);
};

class natural_number_impl : public natural_number_kernel_impl {
public:

    /*
     updates this
     ensures this = #this + 1
     */
    virtual void increment();

    /*
     updates  this
     requires this > 0
     ensures  this = #this - 1
     */
    virtual void decrement();

    /*
     replaces this
     requires n >= 0
     ensures  this = n
     */
    virtual void set_from_long(long n);

    /*
     updates this
     ensures this = #this / 2
     */
    virtual void divide_by_two();

    /*
     ensures add = #x + y
     */
    friend std::tuple<std::unique_ptr<natural_number_impl>, std::unique_ptr<natural_number_impl>> add(std::unique_ptr<natural_number_impl> x, std::unique_ptr<natural_number_impl> y);
    
    /*
     requires x >= y
     ensures  add = #x - y
     */
    friend std::tuple<std::unique_ptr<natural_number_impl>, std::unique_ptr<natural_number_impl>> subtract(std::unique_ptr<natural_number_impl> x, std::unique_ptr<natural_number_impl> y);

    /*
     ensures multiply = #x * y
     */
    friend std::tuple<std::unique_ptr<natural_number_impl>, std::unique_ptr<natural_number_impl>> multiply(std::unique_ptr<natural_number_impl> x, std::unique_ptr<natural_number_impl> y);



};

}

#endif /* natural_number_h */
