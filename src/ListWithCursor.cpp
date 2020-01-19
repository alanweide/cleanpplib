//
//  ListWithCursor.cpp
//  Move Semantics
//
//  Created by Alan Weide on 10/19/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef ListWithCursor_cpp
#define ListWithCursor_cpp

#include "CleanList.hpp"

#include "CleanStack.hpp"
#include "LinkedStack.cpp"
#include "BoundedMovingStack.cpp"

namespace cleanpp {

	template <class T>
	class clean_list: public list_secondary<T> {
	private:
		clean_stack<T>* prec_;
		clean_stack<T>* rem_;

	public:
		clean_list<T>() {
			prec_ = new linked_stack<T>{ };
			rem_ = new linked_stack<T>{ };
		}

		clean_list<T>(clean_list<T> const &other) = delete;
		clean_list<T>(clean_list<T>&& other) {
			prec_ = new linked_stack<T>{std::move(other.prec_)};
			rem_ = new linked_stack<T>{std::move(other.rem_)};
			other.clear(); // done "for free" by previous two statements in this case
		}

		clean_list<T>& operator=(clean_list<T> const &other) = delete;
		clean_list<T>& operator=(clean_list<T>&& other) {
			if (&other == this) {
				return this;
			}
			prec_ = std::move(other.prec_);
			rem_ = std::move(other.rem_);
			other.clear(); // done "for free" by previous two statements in this case
			return this;
		}

		void clear() {
			prec_->clear();
			rem_->clear();
		}

		void swap(clean_list<T>& other) {
			prec_->swap(other.prec_);
			rem_->swap(other.rem_);
		}

		void advance() {
			T x{ };
			rem_->pop(x);
			prec_->push(x);
		}

		void retreat() {
			T x{ };
			prec_->pop(x);
			rem_->push(x);
		}

		void insert(T& x) {
			prec_->push(x);
		}

		void remove(T& x) {
			prec_->pop(x);
		}

		bool isAtEnd() {
			return rem_->isEmpty();
		}

		bool isAtFront() {
			return prec_->isEmpty();
		}
		
		std::ostream& print(std::ostream& out) {
			out << "(";
			clean_stack<T>* rev_prec = new linked_stack<T>{ };
			while (!prec_->isEmpty()) {
				T x;
				prec_->pop(x);
				rev_prec->push(x);
			}
			out << *rev_prec;
			while (!rev_prec->isEmpty()) {
				T x;
				rev_prec->pop(x);
				prec_->push(x);
			}
			out << ", " << *rem_ << ")";
			return out;
		}

	};

}

#endif /* ListWithCursor_cpp */
