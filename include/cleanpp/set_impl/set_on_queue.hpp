//
// set_on_queue.hpp
// Move Semantics

#ifndef set_on_queue_h
#define set_on_queue_h


#include <sstream>
#include <memory>

#include <clean_base.hpp>
#include <set_impl/set_impl.hpp>
#include <queue.hpp>
#include <queue_impl/linked_queue.hpp>


namespace cleanpp
{
template <typename T>
class set_impl;

template <typename T>
class set_on_queue : public set_impl<T> {

private:

    queue<T> rep;
    int size;

    std::tuple<queue<T>, T> moveToFront(queue<T> q, T x) {

        int i = 0;

        T front = q.dequeue();

        while (i < size && !(front == x)) {

            q.enqueue(std::move(front));
            front = q.dequeue();
            i++;

        }

        queue<T> temp;
        while (!q.is_empty()) {
            temp.enqueue(q.dequeue());
        }
        q.enqueue(std::move(front));

        while (!temp.is_empty()) {
            q.enqueue(temp.dequeue());
        }

        return std::make_tuple(std::move(q), std::move(x));
    }

    void createNewRep() {

        this->rep = linked_queue<T>();
        this->size = 0;

    }

    /**
     * Constructors ------------------------------------------------------
     **/

public:

    set_on_queue<T>() {
        this->createNewRep();
    }

    set_on_queue<T>& operator=(const set_on_queue<T>& other) = delete;

    set_on_queue<T>& operator=(set_on_queue<T>&& other) {
        if (&other == this) {
            return *this;
        }

        this->rep = std::move(other.rep);
        this->size = std::move(other.size);
        other.clear();

        return *this;
    }

    void clear() {
        this->rep.clear();
        size = 0;
    }

    /**
     * Kernel methods----------------------------------------------------
     */

    void add(T&& x) {

        this->rep.enqueue(std::forward<T>(x));
        size++;

    }

    T remove(T&& x) {

        std::tie(this->rep, x) = moveToFront(std::move(this->rep), std::move(x));

        size--;
        return this->rep.dequeue();

    }

    T removeAny() {

        size--;
        return this->rep.dequeue();
    }

    std::tuple<bool, T> contains(T&& x) {
        bool has = false;

        // Recursive implementation
        // if (!this->rep.is_empty()) {
        //     T guess = this->rep.dequeue();
        //     has = (guess == x) || this->contains(std::move(x));
        //     this->rep.enqueue(std::move(guess));
        // }
        
        // Iterative Implementation
//        queue<T> temp;
//        while (!has && !this->rep.is_empty()) {
//            T item = this->rep.dequeue();
//            has = (item == x);
//            temp.enqueue(std::move(item));
//        }
//        while (!temp.is_empty()) {
//            T item = temp.dequeue();
//            this->rep.enqueue(std::move(item));
//        }
        
        // Will's implementation (fixed seg fault)
       if(!this->rep.is_empty()){
           std::tie(this->rep, x) = moveToFront(std::move(this->rep), std::move(x));
           T front = this->rep.dequeue();
           if(front == x){
               has = true;
           }
           this->rep.enqueue(std::move(front));
       }

        return std::make_tuple(has, std::move(x));

    }

    bool isEmpty() {
        return this->rep.is_empty();
    }

    int getSize() {
        return size;
    }

    void getElements() {
        std::cout << this->to_str() << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& out, set_on_queue<T>& o) {
        return out << o.to_str();
    }

private:

    std::string to_str() {

        std::stringstream out;

        out << "{";
        queue<T> temp;

        while (!this->rep.is_empty()) {
            T elem;
            elem = this->rep.dequeue();
            out << elem;

            if (!this->rep.is_empty()) {
                out << ", ";
            }
            temp.enqueue(std::move(elem));
        }

        while (!temp.is_empty()) {
            T elem;
            elem = temp.dequeue();
            this->rep.enqueue(std::move(elem));
        }
        out << "}";
        return out.str();
    }



};



}

#endif /* set_on_queue_h */
