//
//  CleanBase.hpp
//  Move Semantics
//
//  Created by Alan Weide on 12/11/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef CleanBase_h
#define CleanBase_h

//using std::swap;

namespace cleanpp {

	template<class T>
	class clean_base {
	public:
//		virtual void swap(clean_base<T>& other) = 0;
		virtual void clear() = 0;

		clean_base<T>() = default;

//		clean_base<T>(clean_base<T> const &other) = delete;
		clean_base<T>(clean_base<T> &&other) {
			*this = std::move(other);
		}

		void foo() {
			int i = 42;
			std::cout << i;
		}

//		clean_base<T>& operator=(clean_base<T> const &other) = delete;
//		virtual clean_base<T>& operator=(clean_base<T>&& other) = 0;

		virtual std::ostream& print(std::ostream& out) = 0;
		friend std::ostream& operator<<(std::ostream& out, clean_base<T>& o) {
			return o.print(out);
		}
	};
}

#endif /* CleanBase_h */
