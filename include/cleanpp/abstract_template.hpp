//
//  abstract_template.hpp
//  Cleanpp
//
//  Created by Alan Weide on 1/29/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef abstract_template_hpp
#define abstract_template_hpp

#include <stdio.h>
#include <clean_nn/natural_number.hpp>

template <typename T>
class abstract_template {
    std::unique_ptr<T> ptr_;
    
public:
};

#endif /* abstract_template_hpp */
