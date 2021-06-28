#ifndef map_h
#define map_h


#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>
#include <map_impl/map_on_set.hpp>
#include <set_impl/set_impl.hpp>
#include <set_impl/set_on_queue.hpp>



namespace cleanpp
{

template <typename K, typename V>
using _map_def_t = map_on_set<K, V>;

template <typename K, typename V>
class map_kernel : public clean_base {

    /*
        map is modeled by finite set of pair
    */

protected:
    std::unique_ptr<map_kernel_impl<K, V>> rep_;

public:

    /**
     * @brief no argument constructor
     *
     * @ensures this = {}
     */
    map_kernel() : rep_(std::make_unique<_map_def_t<K, V>>()) { }

    template<template<typename, typename> class I>
    map_kernel(__attribute__((unused)) const I<K, V>& impl) : rep_(std::make_unique<I<K, V>>()) {
        static_assert(std::is_base_of<map_kernel_impl<K, V>, I<K, V>>::value,
            "Template parameter I must derive from cleanpp::map");
    }

    map_kernel(const map_kernel<K, V>& o) = delete;


    /**
     * @brief Custom move constructor
     *
     * @param other - the map being moved from
     */
    map_kernel(map_kernel<K, V>&& other) : rep_(std::move(other.rep_)) {
        other.rep_ = std::make_unique<_map_def_t<K, V>>();
    }


    map_kernel<K, V>& operator=(const map_kernel<K, V>& other) = delete;


    /**
     * @brief custom move assignment operator
     *
     * @param other - the map being moved from
     * @return the newly-assigned this
     * @ensures this = #other
     */
    map_kernel<K, V>& operator=(map_kernel<K, V>&& other) {
        if (&other == this) {
            return *this;
        }
        rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_map_def_t<K, V>>();
        return *this;
    }


    /**
     * @brief clears this
     */
    void clear() {
        this->rep_->clear();
    }


    /**
     * @brief Adds the pair (key, value) to this
     *
     * @param key - the key to be added
     * @param value - the associated value to be added
     *
     * @requires key is not in DOMAIN(this)
     * @ensures this = #this union {(key, value)}
     */
    void add(K&& key, V&& value) {

        this->rep_->add(std::move(key), std::move(value));
    }


    /**
     * @brief Reports whether there is a pair in this whose first component is key
     *
     * @param key - the key to be checked
     * @return true iff there is a pair in this whose first component is key
     * @ensures hasKey = (key is in DOMAIN(this))
     */
    bool hasKey(K&& key) {
        return this->rep_->hasKey(std::move(key));
    }


    /**
     * @brief Removes the pair whose first component is key and returns it
     *
     * @param key - the key to be removed
     * @return the pair removed
     * @requires key is in DOMAIN(this)
     * @ensures remove.key = key and remove is in #this and this = #this \ {remove}
     */
    pair<K, V> remove(K&& key) {
        return this->rep_->remove(std::forward<K>(key));
    }


    /**
     * @brief Removes and returns an arbitrary pair from this
     *
     * @return the pair removed from this
     * @requires |this| > 0
     * @ensures removeAny is in #this and this = #this \ {removeAny}
     */
    pair<K, V> removeAny() {
        return this->rep_->removeAny();
    }


    /**
     * @brief Reports the size of this
     *
     * @return the number of pairs in this
     * @ensures size = |this|
     */
    int size() {
        return this->rep_->size();
    }

    friend std::ostream& operator<<(std::ostream& out, map_kernel<K, V>& o) {
        return out << *o.rep_;
    }


};

template <typename K, typename V>
class map : public map_kernel<K, V> {
public:

    map() : map_kernel<K, V>() { }

    template<template<typename, typename> class I>
    map(__attribute__((unused)) const I<K, V>& impl) : map_kernel<K, V>(impl) {
        static_assert(std::is_base_of<map_impl<K, V>, I<K, V>>:: value,
            "Type of impl must derive from map");
    }

    map(const map& other) = delete;

    /*
     clears other
     initialization ensures this = #other
    */
    map(map&& other) : map_kernel<K, V>(std::forward<map_kernel<K, V>>(other)) { }

    map& operator=(const map& other) = delete;
    /*
     clears other
     replaces this
     ensures this = #other
    */
    map& operator=(map&& other) { 
        if(&other == this) {
            return *this;
        }
        this->rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_map_def_t<K, V>>();
        return *this;
    }

    /*
     updates this
     clears m
     requires DOMAIN(#this) intersection DOMAIN(#m) = {}
     ensures this = #this union #m
    */
    void combine_with(map<K, V> m) {
        std::unique_ptr<map_impl<K, V>> casted_this(static_cast<map_impl<K, V>*>(this->rep_.release()));
        std::unique_ptr<map_impl<K, V>> casted_m(static_cast<map_impl<K, V>*>(m.rep_.release()));

        casted_this->combine_with(std::move(casted_m));

        this->rep_ = std::move(casted_this);
        m.rep_ = std::make_unique<_map_def_t<K, V>>();
    }


};


}

#endif /* map_h */

