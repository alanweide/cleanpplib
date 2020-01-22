//
//  clean_base.hpp
//  Move Semantics
//
//  Created by Alan Weide on 12/11/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef clean_base_h
#define clean_base_h

//using std::swap;

#include <iostream>

namespace cleanpp {

	template<class T>
	class clean_base {
	public:
//		virtual void swap(clean_base<T>& other) = 0;
		virtual void clear() = 0;

		clean_base<T>() = default;

//		clean_base<T>(clean_base<T> const &other) = delete;
//		clean_base<T>(clean_base<T> &&other) {
//			*this = std::move(other);
//		}

//		clean_base<T>& operator=(clean_base<T> const &other) = delete;
//		virtual clean_base<T>& operator=(clean_base<T>&& other) = 0;

        virtual std::ostream& print(std::ostream& out) {
            return out << this;
        }
        friend std::ostream& operator<<(std::ostream& out, clean_base<T>& o) {
			return o.print(out);
		}
	};
}

#endif /* clean_base_h */
