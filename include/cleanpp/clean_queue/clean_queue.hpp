//
//  clean_queue.hpp
//  Move Semantics
//
//  Created by Alan Weide on 1/15/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#ifndef clean_queue_h
#define clean_queue_h

#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>

namespace cleanpp {
	template <typename T>  // template definition
	class queue: public clean_base
	{
    private:
        virtual std::string to_str() = 0;
	public:
		virtual void enqueue(T& x) = 0;
		virtual void dequeue(T& x) = 0;
		virtual bool is_empty() const = 0;
        
        friend std::ostream& operator<<(std::ostream& out, queue<T>& o) {
            return out << o.to_str();
        }
	};
}

#endif /* clean_queue_h */
