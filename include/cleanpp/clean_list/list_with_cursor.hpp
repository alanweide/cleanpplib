//
//  list_with_cursor.hpp
//  Move Semantics
//
//  Created by Alan Weide on 10/19/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef list_with_cursor_h
#define list_with_cursor_h

#include "CleanList.hpp"

#include <linked_stack.hpp>
#include <bounded_stack.hpp>

namespace cleanpp {

	template <typename T>
	class list_with_cursor: public list_secondary<T> {
	private:
		std::unique_ptr<clean_stack<T>> prec_;
		std::unique_ptr<clean_stack<T>> rem_;
	public:
		list_with_cursor<T>() {
            prec_ = std::make_unique<linked_stack<T>>();
			rem_ = std::make_unique<linked_stack<T>>();
		}

		list_with_cursor<T>(clean_list<T> const &other) = delete;
		list_with_cursor<T>(clean_list<T>&& other) {
			prec_ = std::move(other.prec_);
			rem_ = std::move(other.rem_);
			other.clear(); // done "for free" by previous two statements in this case
		}

		list_with_cursor<T>& operator=(clean_list<T> const &other) = delete;
		list_with_cursor<T>& operator=(clean_list<T>&& other) {
			if (&other == this) {
				return this;
			}
			prec_ = std::move(other.prec_);
			rem_ = std::move(other.rem_);
			other.clear(); // done "for free" by previous two statements in this case
			return this;
		}
        
        bool operator==(list_with_cursor<T> &other) override {
            return *(this->prec_) == *(other.prec_) && *(this->rem_) == *(other.rem_);
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
