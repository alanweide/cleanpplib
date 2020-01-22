//
//  CleanQueue.hpp
//  Move Semantics
//
//  Created by Alan Weide on 1/15/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#ifndef CleanQueue_hpp
#define CleanQueue_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>

namespace cleanpp {
	template <typename T>  // template definition
	class queue: public clean_base<T>
	{
	public:
		virtual void enqueue(std::unique_ptr<T>& x) = 0;
		virtual void dequeue(std::unique_ptr<T>& x) = 0;
		virtual bool isEmpty() const = 0;
	};
}

#endif /* CleanQueue_hpp */
