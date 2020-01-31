//
//  stack_based_list.hpp
//  Move Semantics
//
//  Created by Alan Weide on 10/19/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef stack_based_list_h
#define stack_based_list_h

#include "clean_list.hpp"

#include <clean_stack/linked_stack.hpp>

namespace cleanpp {

	template <typename T>
	class stack_based_list: public list_secondary<T> {
	private:
		std::unique_ptr<clean_stack<T>> prec_;
		std::unique_ptr<clean_stack<T>> rem_;
	public:
		stack_based_list<T>() {
            prec_ = std::make_unique<linked_stack<T>>();
			rem_ = std::make_unique<linked_stack<T>>();
		}

		stack_based_list<T>(stack_based_list<T> const &other) = delete;
		stack_based_list<T>(stack_based_list<T>&& other) {
			prec_ = std::move(other.prec_);
			rem_ = std::move(other.rem_);
			other.clear(); // done "for free" by previous two statements in this case
		}

		stack_based_list<T>& operator=(stack_based_list<T> const &other) = delete;
		stack_based_list<T>& operator=(stack_based_list<T>&& other) {
			if (&other == this) {
				return this;
			}
			prec_ = std::move(other.prec_);
			rem_ = std::move(other.rem_);
			other.clear(); // done "for free" by previous two statements in this case
			return this;
		}
        
        bool operator==(stack_based_list<T> &other) {
            return *(this->prec_) == *(other.prec_) && *(this->rem_) == *(other.rem_);
        }

		void clear() override {
			prec_->clear();
			rem_->clear();
		}

		void swap(stack_based_list<T>& other) {
			prec_->swap(other.prec_);
			rem_->swap(other.rem_);
		}

		void advance() override {
			T x{ };
			rem_->pop(x);
			prec_->push(x);
		}

		void retreat() override {
			T x{ };
			prec_->pop(x);
			rem_->push(x);
		}

		void insert(T& x) override {
			prec_->push(x);
		}

		void remove(T& x) override {
			rem_->pop(x);
		}

		bool is_at_end() override {
			return rem_->is_empty();
		}

		bool is_at_front() override {
			return prec_->is_empty();
		}
		
		std::string to_str() override {
            std::stringstream out;
			out << "(";
			std::unique_ptr<clean_stack<T>> rev_prec = std::make_unique<linked_stack<T>>();
			while (!prec_->is_empty()) {
				T x;
				prec_->pop(x);
				rev_prec->push(x);
			}
			out << *rev_prec;
			while (!rev_prec->is_empty()) {
				T x;
				rev_prec->pop(x);
				prec_->push(x);
			}
			out << ", " << *rem_ << ")";
            return out.str();
		}

	};

}

#endif /* ListWithCursor_cpp */
