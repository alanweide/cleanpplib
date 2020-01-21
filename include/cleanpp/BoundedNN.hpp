//
//  BoundedNN.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef BoundedNN_h
#define BoundedNN_h

#include <NaturalNumber.hpp>

namespace cleanpp {
class bounded_nn: public natural_number {
private:
    int n;
public:
    bounded_nn();
    
    bounded_nn(bounded_nn const &other) = delete;
    bounded_nn(bounded_nn&& other);
    
    bounded_nn& operator=(const bounded_nn& other) = delete;
    bounded_nn& operator=(bounded_nn&& other);
    
    void clear() override;
    bool is_zero() override;
    void multiply_by_radix(int d) override;
    void divide_by_radix(int &d) override;
    void increment() override;
    void decrement() override;
    void set_from_int(int n) override;
    
    std::ostream& print(std::ostream& out) override;
};
}


#endif /* BoundedNN_h */
