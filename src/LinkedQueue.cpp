//
//  LinkedQueue.cpp
//  Move Semantics
//
//  Created by Alan Weide on 1/17/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#ifndef LinkedQueue_cpp
#define LinkedQueue_cpp

#include "CleanQueue.hpp"

namespace cleanpp {
	
	template <typename T>
	class clean_queue: public clean_base<T> {
	private:
		class queue_node {
		private:
			void clear() {
				contents = T();
				next.reset();
			}
		public:
			std::unique_ptr<T> contents;
			std::shared_ptr<queue_node> next;
			
			queue_node(): contents(), next() {}
			
			queue_node(std::unique_ptr<T>& new_contents):
			contents(std::move(new_contents)), next() {}

			queue_node(queue_node const &other) = delete;
			queue_node(queue_node&& other):
			contents(std::move(other.contents)),
			next(std::move(other.next)) {
				other.clear();
			}
			
			queue_node& operator=(const queue_node& other) = delete;
			queue_node& operator=(queue_node&& other) {
				if (&other == this) {
					return *this;
				}
				contents = std::move(other.contents);
				next = std::move(other.next);
				other.clear();
				return *this;
			}
			
			friend std::ostream& operator<<(std::ostream& out, const queue_node& node) {
				return out << node.contents;
			}
			
		};
		
		std::shared_ptr<queue_node> top_ptr_;
		std::shared_ptr<queue_node> tail_ptr_;
	public:
		clean_queue<T>(): top_ptr_(), tail_ptr_() { }
		
		clean_queue<T>(clean_queue<T> const &other) = delete;
		clean_queue<T>(clean_queue<T>&& other):
		top_ptr_(std::move(other.top_ptr_)),
		tail_ptr_(std::move(other.tail_ptr_)) {
			other.clear();
		}
		
		clean_queue<T>& operator=(const clean_queue<T>& other) = delete;
		clean_queue<T>& operator=(clean_queue<T>&& other) {
			if (&other == this) {
				return *this;
			}
			
			top_ptr_ = std::move(other.top_ptr_);
			tail_ptr_ = std::move(other.tail_ptr_);
			other.clear();
			return *this;
		}
		
		void clear() {
			top_ptr_.reset();
			tail_ptr_.reset();
		}
		
//		void swap(linked_queue<T>& other) {
//			std::swap(top_ptr_, other.top_ptr_);
//			std::swap(tail_ptr_, other.tail_ptr_);
//		}
		
		void enqueue(std::unique_ptr<T>& x) {
			auto new_tail = std::make_shared<queue_node>(std::move(x));
			if (tail_ptr_ != nullptr) {
				tail_ptr_->next = new_tail;
			} else {
				top_ptr_ = new_tail;
			}
			
			// Alias!!
			tail_ptr_ = new_tail;
		}
		
		void dequeue(std::unique_ptr<T>& x) {
			std::swap(x, top_ptr_->contents);
			std::swap(top_ptr_, top_ptr_->next);
		}
		
		bool isEmpty() const {
			return top_ptr_ == nullptr;
		}
		
		std::ostream& print(std::ostream& out) {
			out << "<";
			clean_queue<T> temp{};
			while (!isEmpty())
			{
				std::unique_ptr<T> elem;
				dequeue(elem);
				out << elem;
				if (!isEmpty())
				{
					out << ", ";
				}
				temp.enqueue(elem);
			}
			std::swap(*this, temp);
			return out << ">";
		}
	};
	
}

#endif // LinkedQueue_cpp
