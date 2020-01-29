//
//  clean_base.hpp
//  Move Semantics
//
//  Created by Alan Weide on 12/11/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef clean_base_h
#define clean_base_h

#include <iostream>

namespace cleanpp {

	class clean_base {
	public:
		clean_base() = default;
        virtual ~clean_base() = default;

//        virtual clean_base<T> operator=(clean_base<T> &other) = delete;
//        virtual clean_base<T> operator=(clean_base<T> &&other) = 0;
        
        virtual void clear() = 0;
    };
}

#endif /* clean_base_h */
