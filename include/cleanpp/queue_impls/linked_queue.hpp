//
//  linked_queue.hpp
//  Move Semantics
//
//  Created by Alan Weide on 1/17/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#ifndef linked_queue_h
#define linked_queue_h

#include <sstream>

#include "queue_impl.hpp"

namespace cleanpp {

template <typename T>
class linked_queue: public queue_impl<T> {
private:
    class queue_node: public clean_base {
    private:
        std::unique_ptr<T> contents_;
        std::shared_ptr<queue_node> next_;
    public:
        queue_node(): contents_(), next_() {}
        
        queue_node(T& new_contents):
        next_() {
            contents_ = std::make_unique<T>(std::move(new_contents));
        }
        
        queue_node(queue_node const &other) = delete;
        queue_node(queue_node&& other):
        contents_(std::move(other.contents_)),
        next_(std::move(other.next_)) {
            other.clear();
        }
        
        queue_node& operator=(const queue_node& other) = delete;
        queue_node& operator=(queue_node&& other) {
            if (&other == this) {
                return *this;
            }
            contents_ = std::move(other.contents_);
            next_ = std::move(other.next_);
            other.clear();
            return *this;
        }
        
        void clear() {
            contents_.reset();
            next_.reset();
        }
        
        T&& contents() {
            return std::move(*contents_);
        }
        
        void set_next(std::shared_ptr<queue_node>& new_next) {
            next_ = new_next;
        }
        
        std::shared_ptr<queue_node>&& next() {
            return std::move(next_);
        }
        
        friend std::ostream& operator<<(std::ostream& out, const queue_node& node) {
            return out << *node.contents_;
        }
        
    };
    
    std::shared_ptr<queue_node> top_ptr_;
    std::shared_ptr<queue_node> tail_ptr_;
public:
    linked_queue<T>(): top_ptr_(), tail_ptr_() { }
    
    linked_queue<T>(linked_queue<T> const &other) = delete;
    linked_queue<T>(linked_queue<T>&& other):
    top_ptr_(std::move(other.top_ptr_)),
    tail_ptr_(std::move(other.tail_ptr_)) {
        other.clear();
    }
    
    linked_queue<T>& operator=(const linked_queue<T>& other) = delete;
    linked_queue<T>& operator=(linked_queue<T>&& other) {
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
    
    void enqueue(T&& x) {

        auto new_tail = std::make_shared<queue_node>(x);
        if (tail_ptr_ != nullptr) {
            tail_ptr_->set_next(new_tail);
        } else {
            top_ptr_ = new_tail;
        }
        
        // Potential alias (tail_ptr_ & top_ptr_)
        tail_ptr_ = new_tail;

    }
    
    T dequeue() {

        T x = top_ptr_->contents();
        top_ptr_ = top_ptr_->next();

        // Add this to fix enq_deq_enq_deq problem
        if (top_ptr_ == nullptr){
            tail_ptr_ = nullptr;
        }

		return std::move(x);
    }
    
    bool is_empty() const {
        return top_ptr_ == nullptr;
    }


    
private:
    std::string to_str() {
        std::stringstream out;
        out << "<";
        std::unique_ptr<queue_impl<T>> temp = std::make_unique<linked_queue<T>>();
        while (!this->is_empty())
        {
            T elem;
            elem = this->dequeue();
            out << elem;
            if (!this->is_empty())
            {
                out << ", ";
            }
            temp->enqueue(std::move(elem));
        }
//        this(std::move(*temp));
        while (!temp->is_empty())
        {
            T elem;
            elem = temp->dequeue();
            this->enqueue(std::move(elem));
        }
        out << ">";
        return out.str();
    }
};

}

#endif /* linked_queue_h */
