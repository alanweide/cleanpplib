//
//  BoundedQueue.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#ifndef BoundedQueue_h
#define BoundedQueue_h

#include "CleanQueue.hpp"

namespace cleanpp {
	
	template <class T>
	class bounded_queue: public queue<T>
	{
	private:
		static const int MAX_SIZE = 6;
		
		int head_;
		int length_;
		int init_so_far_;
		std::unique_ptr<T>* contents_;
		
	public:
			
		bounded_queue()
		{
			head_ = 0;
			length_ = 0;
			init_so_far_ = 0;
			contents_ = new std::unique_ptr<T>[MAX_SIZE];
			//		for (int i = 0; i < MAX_SIZE; i++) {
			//			contents_[i] = std::make_unique<T>();
			//		}
		}
		
		~bounded_queue() {
			delete [] contents_;
		}
		
//		void swap(bounded_queue<T>& other) {
//			int head_t = other.head_;
//			int length_t = other.length_;
//			int init_so_far_t = other.init_so_far_;
//			auto contents_t = std::move(other.contents_);
//
//			other.length_ = length_;
//			other.head_ = head_;
//			other.init_so_far_ = init_so_far_;
//			other.contents_ = std::move(contents_);
//
//			head_ = head_t;
//			length_ = length_t;
//			init_so_far_ = init_so_far_t;
//			contents_ = std::move(contents_t);
//		}
		
		void clear() override;
		
		void enqueue(std::unique_ptr<T>& x) override;
		
		void dequeue(std::unique_ptr<T>& x) override;
		
		bool isEmpty() const override;
		
		std::ostream& print(std::ostream& out) override;
	};
}

#endif /* BoundedQueue_h */
