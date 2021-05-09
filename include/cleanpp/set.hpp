#ifndef set_h
#define set_h


#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>
#include <set_impl/set_impl.hpp>
#include <set_impl/set_on_queue.hpp>


namespace cleanpp
{

template <typename I>
using _set_def_t = set_on_queue<I>;

template <typename Item>
class set : public clean_base {

    /*
    set is modeled by finite set of Item
    */

protected:
    std::unique_ptr<set_impl<Item>> rep_;

public:


    /**
     * @brief No argument constructor
     *
     * @ensures this = {}
     */
    set() : rep_(std::make_unique<_set_def_t<Item>>()) { }

    template<template<typename> class I>
    set(__attribute__((unused)) const I<Item>& impl) : rep_(std::make_unique<I<Item>>()) {
        static_assert(std::is_base_of<set_impl<Item>, I<Item>>::value,
            "Template parameter I must derive from cleanpp::set");
    }

    set(const queue<Item>& o) = delete;


    /**
     * @brief Custom move constructor
     *
     * @param other - set to move from
     * @ensures this = #other
     */
    set(set<Item>&& other) : rep_(std::move(other.rep_)) {
        other.rep_ = std::make_unique<_set_def_t<Item>>();
    }

    set<Item>& operator=(const set<Item>& other) = delete;


    /**
     * @brief Overloaded move assignment operator
     *
     * @param other - set to move from
     * @return the newly-assigned this
     * @ensures this = #other
     */
    set<Item>& operator=(set<Item>&& other) {
        if (&other == this) {
            return *this;
        }
        rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_set_def_t<Item>>();
        return *this;
    }


    /**
     * @brief Resets this to default initial value
     *
     */
    void clear() {
        this->rep_->clear();
    }


    /**
     * @brief Adds x to this
     *
     * @param x the element to be added
     * @requires x is not in this
     * @ensures this = #this union {x}
     *
     */
    void add(Item&& x) {
        rep_->add(std::forward<Item>(x));
    }


    /**
     * @brief Reports whether x is in this.
     *
     * @param x - the element to be checked
     * @return true iff element is in this
     * @ensures contains = (x is in this)
     */
    bool contains(Item&& x) {
        return rep_->contains(std::forward<Item>(x));
    }


    /**
     * @brief Removes x from this, and returns it.
     *
     * @param x
     * @return the element removed
     * @requires x is in this
     * @ensures this = #this \ {x} and remove = x
     */
    Item remove(Item&& x) {
        return rep_->remove(std::forward<Item>(x));
    }


    /**
     * @brief Removes and returns an arbitrary element from this
     *
     * @return the element removed fromt this
     * @requires |this| > 0
     * @ensures removeAny is in #this and this = #this \ {removeAny}
     */
    Item removeAny() {
        return rep_->removeAny();
    }


    /**
     * @brief Reports size (cardinality) of this
     *
     * @return the number of elements in this
     * @ensures getSize = |this|
     */
    int getSize() {
        return rep_->getSize();
    }

    bool isEmpty() {
        return rep_->isEmpty();
    }

    bool is_empty() {
        return rep_->isEmpty();
    }


    /**
     * @brief Overloaded equality operator for sets
     *
     * @param other - set to compare to
     * @return true iff sets contain the same elements
     */
    bool operator==(set<Item>& other) {
        return *this->rep_ == *other.rep_;
    }

    friend std::ostream& operator<<(std::ostream& out, set<Item>& o) {
        return out << *o.rep_;
    }


};


}

#endif /* set_h */
