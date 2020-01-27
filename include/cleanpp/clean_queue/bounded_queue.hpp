//
//  bounded_queue.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#ifndef bounded_queue_h
#define bounded_queue_h

#include <clean_queue.hpp>

namespace cleanpp {

template <class T>
class bounded_queue: public clean_queue<T>
{
private:
    static const int MAX_SIZE = 6;
    
    int head_;
    int length_;
    int init_so_far_;
    T* contents_;
    
public:
    
    bounded_queue()
    {
        head_ = 0;
        length_ = 0;
        init_so_far_ = 0;
        contents_ = new T[MAX_SIZE];
        //		for (int i = 0; i < MAX_SIZE; i++) {
        //			contents_[i] = std::make_unique<T>();
        //		}
    }
    
    ~bounded_queue() {
        delete [] contents_;
    }
    
    void clear() {
        length_ = 0;
    }
    
    void enqueue(T& x)
    {
        int next_idx = (head_ + length_) % MAX_SIZE;
        if (init_so_far_ <= next_idx) {
            init_so_far_++;
        }
        contents_[next_idx] = std::move(x);
        length_++;
    }
    
    void dequeue(T& x)
    {
        x = std::move(contents_[head_]);
        length_--;
        head_ = (head_ + 1) % MAX_SIZE;
    }
    
    bool isEmpty() const {
        return length_ == 0;
    }
    
    std::ostream& print(std::ostream& out) {
        out << "<";
        int i = 0;
        while (i < length_)
        {
            int idx = (head_ + i) % MAX_SIZE;
            out << contents_[idx];
            i++;
            if (i < length_)
            {
                out << ", ";
            }
        }
        out << ">";
        return out;
    }
};
}

#endif /* bounded_queue_h */
