//
//  CleanQueue.cpp
//  Move Semantics
//
//  Created by Alan Weide on 1/15/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#ifndef BoundedQueue_cpp
#define BoundedQueue_cpp

#include "BoundedQueue.hpp"

namespace cleanpp {

template<class T>
void bounded_queue<T>::clear() {
	length_ = 0;
}

template<class T>
void bounded_queue<T>::enqueue(std::unique_ptr<T>& x)
{
	int next_idx = (head_ + length_) % MAX_SIZE;
	if (init_so_far_ <= next_idx) {
		contents_[next_idx] = std::make_unique<T>();
		init_so_far_++;
	}
	std::swap(x, contents_[next_idx]);
	length_++;
}

template<class T>
void bounded_queue<T>::dequeue(std::unique_ptr<T>& x)
{
	std::swap(x, contents_[head_]);
	length_--;
	head_ = (head_ + 1) % MAX_SIZE;
}

template<class T>
bool bounded_queue<T>::isEmpty() const {
	return length_ == 0;
}

template<class T>
std::ostream& bounded_queue<T>::print(std::ostream& out) {
	out << "<";
	int i = 0;
	while (i < length_)
	{
		int idx = (head_ + i) % MAX_SIZE;
		out << *contents_[idx];
		i++;
		if (i < length_)
		{
			out << ", ";
		}
	}
	out << ">";
	return out;
}
}

#endif // BoundedQueue_cpp
