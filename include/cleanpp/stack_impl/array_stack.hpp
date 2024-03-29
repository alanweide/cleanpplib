//
//  array_stack.hpp
//  Move Semantics
//
//  Created by Alan Weide on 9/25/18.
//  Copyright © 2018 Alan Weide. All rights reserved.
//

#ifndef array_stack_h
#define array_stack_h

#include <stdio.h>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>

#include "stack_impl.hpp"

namespace cleanpp
{

template <typename T>
class array_stack : public stack_impl<T> {
private:
	static const int MIN_CAP = 1;
	static const int GROW_FAC = 2;
	static const int SHRINK_FAC = 4;
	int cap_;

	int length_;
	std::unique_ptr<T[ ]> contents_;

	std::string to_str() override {
		std::stringstream out;
		out << "<";
		int i = length_;
		while (i > 0) {
			i--;
			out << contents_[i];
			if (i > 0) {
				out << ", ";
			}
		}
		out << ">";
		return out.str();
	}

	void resize_if_needed() {
		int old_cap = cap_;
		if (length_ >= cap_) {
			cap_ = length_ * GROW_FAC;
		} else if (length_ * SHRINK_FAC < cap_) {
			cap_ /= SHRINK_FAC;
			if (cap_ < MIN_CAP) {
				cap_ = MIN_CAP;
			}
		}
		if (cap_ != old_cap) {
			auto temp_cont = std::move(contents_);
			contents_ = std::make_unique<T[ ]>(cap_);
			for (int i = 0; i < length_; i++) {
				contents_[i] = std::move(temp_cont[i]);
			}
		}
	}

public:

	array_stack<T>() :
		cap_(MIN_CAP), length_(0) {
		contents_ = std::make_unique<T[ ]>(cap_);
	}

	array_stack<T>(array_stack<T> const& other) = delete;
	array_stack<T>(array_stack<T>&& other) :
		cap_(std::move(other.cap_)), length_(std::move(other.length_)), contents_(std::move(other.contents_)) {
		other.clear();
	}

	array_stack<T>& operator=(const array_stack<T>& other) = delete;
	array_stack<T>& operator=(array_stack<T>&& other) {
		if (&other == this) {
			return *this;
		}

		cap_ = std::move(other.cap_);
		length_ = std::move(other.length_);
		contents_ = std::move(other.contents_);
		other.clear();
		return *this;
	}

	~array_stack() { }

	void clear() override {
		length_ = 0;
	}

    std::unique_ptr<stack_impl<T>> new_instance() override {
        return std::make_unique<linked_stack<T>>();
    }

	void push(T&& x) override {
		contents_[length_] = std::forward<T>(x);
		length_++;

		resize_if_needed();
	}

	T pop() override {
		assert(!this->is_empty());

		length_--;
		T pop = std::move(contents_[length_]);

		resize_if_needed();

		return std::move(pop);
	}

	bool is_empty() const override {
		return length_ == 0;
	}

};

}

#endif /* array_stack_h */
