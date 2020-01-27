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
	class clean_queue: public clean_base<T>
	{
	public:
		virtual void enqueue(std::unique_ptr<T>& x) = 0;
		virtual void dequeue(std::unique_ptr<T>& x) = 0;
		virtual bool isEmpty() const = 0;
	};
}

#endif /* clean_queue_h */
