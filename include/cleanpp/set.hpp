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
class set_kernel : public clean_base {

    /*
    set is modeled by finite set of Item
    */

protected:
    std::unique_ptr<set_kernel_impl<Item>> rep_;

public:


    /**
     * @brief No argument constructor
     *
     * @ensures this = {}
     */
    set_kernel() : rep_(std::make_unique<_set_def_t<Item>>()) { }

    template<template<typename> class I>
    set_kernel(__attribute__((unused)) const I<Item>& impl) : rep_(std::make_unique<I<Item>>()) {
        static_assert(std::is_base_of<set_kernel_impl<Item>, I<Item>>::value,
            "Template parameter I must derive from cleanpp::set_kernel");
    }

    set_kernel(const queue<Item>& o) = delete;


    /**
     * @brief Custom move constructor
     *
     * @param other - set to move from
     * @ensures this = #other
     */
    set_kernel(set_kernel<Item>&& other) : rep_(std::move(other.rep_)) {
        other.rep_ = std::make_unique<_set_def_t<Item>>();
    }

    set_kernel<Item>& operator=(const set_kernel<Item>& other) = delete;


    /**
     * @brief Overloaded move assignment operator
     *
     * @param other - set to move from
     * @return the newly-assigned this
     * @ensures this = #other
     */
    set_kernel<Item>& operator=(set_kernel<Item>&& other) {
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
    std::tuple<bool, Item> contains(Item&& x) {

        bool has;
        
        std::tie(has, x) = rep_->contains(std::forward<Item>(x));
        return std::make_tuple(std::move(has), std::move(x));
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
    bool operator==(set_kernel<Item>& other) {
        return *this->rep_ == *other.rep_;
    }

    friend std::ostream& operator<<(std::ostream& out, set_kernel<Item>& o) {
        return out << *o.rep_;
    }


};

template <typename Item>
class set : public set_kernel<Item> {
public:

    set() : set_kernel<Item>() { }

    template<template<typename> class I>
    set(__attribute__((unused)) const I<Item>& impl) : set_kernel<Item>(impl) {
        static_assert(std::is_base_of<set_impl<Item>, I<Item>>::value,
            "Type of impl must derive from set");
    }

    set(const set& other) = delete;

    /*
     clears other
     initialization ensures this = #other
    */
    set(set&& other) : set<Item>(std::forward<set_kernel<Item>>(other)) { }

    set& operator=(const set& other) = delete;

    /*
     clears other
     replaces this
     ensures this = #other
    */
    set& operator=(set&& other) {
        if(&other == this) {
            return *this;
        }
        this->rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_set_def_t<Item>>();
        return *this;

    }

    /*
     updates this
     clears s
     ensures this = #this union #s
    */
    set<Item>&& set_union(set<Item>&& s) {
        std::unique_ptr<set_impl<Item>> casted_this(static_cast<set_impl<Item>*>(this->rep_.release()));
        std::unique_ptr<set_impl<Item>> casted_s(static_cast<set_impl<Item>*>(s.rep_.release()));

        casted_s = casted_this->set_union(std::move(casted_s));

        this->rep_ = std::move(casted_this);
        s.rep_ = std::move(casted_s);

        return std::move(s);

    }


};


}

#endif /* set_h */