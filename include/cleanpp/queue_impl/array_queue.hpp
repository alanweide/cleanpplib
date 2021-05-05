//
//  array_queue.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#ifndef array_queue_h
#define array_queue_h

#include "queue_impl.hpp"

namespace cleanpp
{

template <class T>
class array_queue : public queue_impl<T> {
<<<<<<< HEAD
private:
=======
    private:
>>>>>>> 9c62f73e0528c332982fb99bdce70c979ced8529
    static const int MIN_CAP = 6;
    static const int GROW_FAC = 2;
    static const int SHRINK_FAC = 4;

    int cap_;
    int head_;
    int length_;
    std::unique_ptr<T[ ]> contents_;

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
            std::unique_ptr<T[ ]> temp_cont = std::move(contents_);
            contents_ = std::make_unique<T[ ]>(cap_);
            for (int i = 0; i < length_; i++) {
                contents_[i] = std::move(temp_cont[(i + head_) % old_cap]);
            }
            head_ = 0;
        }
    }

<<<<<<< HEAD
public:

    array_queue() : cap_(MIN_CAP), head_(0), length_(0) {
        contents_ = std::make_unique<T[ ]>(cap_);
    }

    ~array_queue() { }
=======
    public:

    array_queue() : cap_(MIN_CAP), head_(0), length_(0)     {
        contents_ = std::make_unique<T[ ]>(cap_);
    }

    ~array_queue() {     }
>>>>>>> 9c62f73e0528c332982fb99bdce70c979ced8529

    void clear() override {
        length_ = 0;
    }

<<<<<<< HEAD
    void enqueue(T&& x) override {
=======
    void enqueue(T&& x) override     {
>>>>>>> 9c62f73e0528c332982fb99bdce70c979ced8529
        int next_idx = (head_ + length_) % cap_;
        contents_[next_idx] = std::move(x);
        length_++;

        this->resize_if_needed();
    }

<<<<<<< HEAD
    T dequeue() override {
=======
    T dequeue() override     {
>>>>>>> 9c62f73e0528c332982fb99bdce70c979ced8529
        T x = std::move(contents_[head_]);

        length_--;

        head_ = (head_ + 1) % cap_;

        this->resize_if_needed();

        return std::move(x);
    }

    bool is_empty() const override {
        return length_ == 0;
    }

    std::string to_str() override {
        std::stringstream out;
        out << "<";
        int i = 0;
<<<<<<< HEAD
        while (i < length_) {
            int idx = (head_ + i) % cap_;
            out << contents_[idx];
            i++;
            if (i < length_) {
=======
        while (i < length_)         {
            int idx = (head_ + i) % cap_;
            out << contents_[idx];
            i++;
            if (i < length_)             {
>>>>>>> 9c62f73e0528c332982fb99bdce70c979ced8529
                out << ", ";
            }
        }
        out << ">";
        return out.str();
    }
};
}

#endif /* array_queue_h */
