//
//  bounded_stack.hpp
//  Move Semantics
//
//  Created by Alan Weide on 9/25/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef bounded_stack_h
#define bounded_stack_h

#include <stdio.h>
#include <memory>
#include <string>
#include <iostream>

#include <clean_stack.hpp>

namespace cleanpp {
	
	template <typename T>
	class bounded_stack: public clean_stack<T>
	{
	private:
		static const int MAX_SIZE = 6;
		
		int length_;
		int init_so_far_;
		T* contents_;
		
	public:
		
		bounded_stack()
		{
			length_ = 0;
			init_so_far_ = 0;
			contents_ = new T[MAX_SIZE];
			//		for (int i = 0; i < MAX_SIZE; i++) {
			//			contents_[i] = std::make_unique<T>();
			//		}
		}
		
		~bounded_stack() {
			delete [] contents_;
		}
		
		void clear() {
			length_ = 0;
		}
		
		void swap(bounded_stack<T>& other) {
			int length_t = other.length_;
			auto contents_t = other.contents_;
			
			other.length_ = length_;
			other.contents_ = std::move(contents_);
			
			length_ = length_t;
			contents_ = contents_t;
		}
		
		void push(T& x)
		{
			//		std::cout << "\nBoundedMovingStack_Hidden::push(T& x):\n";
			
			if (init_so_far_ <= length_) {
				// contents[length] has not been initialized; initialize it by moving x; leave x in an initial state
				contents_[length_] = T{ };
				init_so_far_++;
			}
			T temp = std::move(contents_[length_]);
			contents_[length_] = std::move(x);
			x = std::move(temp);
			length_++;
		}
		
		void pop(T& x)
		{
			//		std::cout << "\nBoundedMovingStack_Hidden::pop(T& x):\n";
			
			length_--;
			T temp = std::move(contents_[length_]);
			contents_[length_] = std::move(x);
			x = std::move(temp);
		}
		
		bool isEmpty() const {
			return length_ == 0;
		}
		
		std::ostream& print(std::ostream& out) {
			out << "<";
			int i = length_;
			while (i > 0)
			{
				i--;
				out << contents_[i];
				if (i > 0)
				{
					out << ", ";
				}
			}
			out << ">";
			return out;
		}
	};
	
	//template <typename T>
	//class BoundedMovingStack_Explicit {
	//private:
	//	static const int MAX_SIZE = 6;
	//
	//	int length_ = 0;
	//	std::unique_ptr<T> contents_[MAX_SIZE];
	//
	//public:
	//	BoundedMovingStack_Explicit()
	//	{
	//		length_ = 0;
	//		for (int i = 0; i < MAX_SIZE; i++) {
	//			contents_[i] = std::make_unique<T>();
	//		}
	//	}
	//
	//	void push(std::unique_ptr<T>& x_ptr)
	//	{
	////		std::cout << "\nBoundedMovingStack_Explicit::push(std::unique_ptr<T>& x_ref):\n";
	//
	//		contents_[length_].swap(x_ptr);
	//		length_++;
	//	}
	//
	//	void pop(std::unique_ptr<T>& x_ptr) {
	////		std::cout << "\nBoundedMovingStack_Explicit::pop(std::unique_ptr<T>& x):\n";
	//
	//		length_--;
	//		x_ptr.swap(contents_[length_]);
	//	}
	//
	//	int length() const {
	//		return length_;
	//	}
	//
	//	friend std::ostream& operator<<(std::ostream& out, const BoundedMovingStack_Explicit& stack)
	//	{
	//
	//		int i = stack.length_;
	//		while (i > 0)
	//		{
	//			i--;
	//			out << *(stack.contents_[i]);
	//			if (i > 0)
	//			{
	//				out << ", ";
	//			}
	//		}
	//		out << ">";
	//		return out;
	//	}
	//};
	
}

#endif /* BoundedMovingStack_cpp */
