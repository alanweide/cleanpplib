//
//  LinkedStack.cpp
//  Move Semantics
//
//  Created by Alan Weide on 12/1/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef LinkedStack_cpp
#define LinkedStack_cpp

#include "CleanStack.hpp"

namespace cleanpp {
	
	template <typename T>
	class linked_stack: public clean_stack<T> {
	private:
		class stack_node {
		private:
			void clear() {
				contents = T();
				next.reset();
			}
		public:
			T contents;
			std::unique_ptr<stack_node> next;
			
			stack_node(): contents(), next() {}
			
			stack_node(stack_node const &other) = delete;
			stack_node(stack_node&& other):
			contents(std::move(other.contents)),
			next(std::move(other.next)) {
				other.clear();
			}
			
			stack_node& operator=(const stack_node& other) = delete;
			stack_node& operator=(stack_node&& other) {
				if (&other == this) {
					return *this;
				}
				contents = std::move(other.contents);
				next = std::move(other.next);
				other.clear();
			}
			
			stack_node(T& new_contents):
			contents(), next() {
				std::swap(contents, new_contents);
			}
			
			friend std::ostream& operator<<(std::ostream& out, const stack_node& node) {
				out << node.contents;
				return out;
			}
			
		};
		
		std::unique_ptr<stack_node> top_ptr_;
	public:
		linked_stack<T>() { }

//		linked_stack<T>(linked_stack<T> const &other) = delete;
//		linked_stack<T>(linked_stack<T>&& other):
//		top_ptr_(std::move(other.top_ptr_)) {
//			other.clear();
//		}
//		linked_stack<T>(linked_stack<T>&& other) {
//			*this = std::move(other);
//		}

//		linked_stack<T>& operator=(const linked_stack<T>& other) = delete;
		linked_stack<T>& operator=(linked_stack<T>&& other) {
			if (&other == this) {
				return *this;
			}
			
			top_ptr_ = std::move(other.top_ptr_);
			other.clear();
		}
		
		void clear() {
			top_ptr_.reset();
		}

		void foo() {
			int i = 76;
			std::cout << i;
		}

//		void swap(linked_stack<T>& other) {
//			top_ptr_.swap(other.top_ptr_);
//		}
		
		void push(T& x) {
			auto new_top = std::make_unique<stack_node>(x);
			std::swap(new_top->next, top_ptr_);
			std::swap(top_ptr_, new_top);
		}
		
		void pop(T& x) {
			std::swap(x, top_ptr_->contents);
			std::swap(top_ptr_, top_ptr_->next);
		}
		
		bool isEmpty() const {
			return top_ptr_ == nullptr;
		}
		
		std::ostream& print(std::ostream& out) {
			out << "<";
			linked_stack<T> temp{};
			while (!isEmpty())
			{
				T top;
				pop(top);
				out << top;
				if (!isEmpty())
				{
					out << ", ";
				}
				temp.push(top);
			}
			while (!temp.isEmpty()) {
				T top;
				temp.pop(top);
				push(top);
			}
			out << ">";
			return out;
		}
	};
	
}

#endif /* LinkedStack_cpp */

