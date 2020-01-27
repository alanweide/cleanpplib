//
//  clean_list.hpp
//  Move Semantics
//
//  Created by Alan Weide on 12/6/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef clean_list_h
#define clean_list_h

#include <stdio.h>
#include <iostream>
#include <clean_base.hpp>

namespace cleanpp {
	template <class T>
	class clean_list: public clean_base<T> {
	public:
		virtual void advance() = 0;
		virtual void retreat() = 0;
		virtual void insert(T& x) = 0;
		virtual void remove(T& x) = 0;
		virtual bool isAtEnd() = 0;
		virtual bool isAtFront() = 0;
	};

	template<class T>
	class list_secondary: public clean_list<T> {
	public:
		virtual void reset() {
			while (!this->isAtFront()) {
				this->retreat();
			}
		}
	};
}

#endif /* clean_list_h */
