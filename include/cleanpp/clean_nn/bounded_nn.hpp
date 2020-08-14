//
//  bounded_nn.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef bounded_nn_h
#define bounded_nn_h

#include <clean_nn/natural_number.hpp>

namespace cleanpp {
class bounded_nn: public natural_number_secondary {
public:
    bounded_nn(long n = 0);
    
    bounded_nn(bounded_nn const &other) = delete;
    bounded_nn(bounded_nn&& other);
	
	~bounded_nn();
    
    bounded_nn& operator=(const bounded_nn& other) = delete;
    bounded_nn& operator=(bounded_nn&& other);
        
    bool operator==(const bounded_nn &other);
    
    void clear() override;
    bool is_zero() const override;
    void multiply_by_radix(int d) override;
    int&& divide_by_radix() override;
    void increment() override;
    void decrement() override;
    void set_from_long(long n) override;
    
    friend std::ostream& operator<<(std::ostream& out, bounded_nn& o) {
        return out << o.n_;
    }
private:
    long n_;
};

}


#endif /* bounded_nn_h */
