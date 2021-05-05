// clean_map.hpp
// Move Semantics

#ifndef clean_map_h
#define clean_map_h


#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>

namespace cleanpp
{

template <typename K, typename V>
class pair : public clean_base {
private:

    std::unique_ptr<K> key;
    std::unique_ptr<V> value;
public:

    pair() : key(), value() { }

    pair(K&& key, V&& value) {
        this->key = std::make_unique<K>(std::move(key));
        this->value = std::make_unique<V>(std::move(value));
    }

    pair(pair const& other) = delete;
    pair(pair&& other) :
        key(std::move(other.key)),
        value(std::move(other.value)) {
        other.clear();
    }

    pair& operator=(const pair& other) = delete;

    pair& operator=(pair&& other) {
        if (&other == this) {
            return *this;
        }

        key = std::move(other.key);
        value = std::move(other.value);
        other.clear();
        return *this;
    }

    void clear() {
        key.reset();
        value.reset();
    }

    V getValue(K&& key) {
        return std::move(*this->value);
    }

    bool operator==(pair& other) {
        return *this->key == *other.key;
    }

    bool operator==(K& key) {
        return *this->key == key;
    }

    friend std::ostream& operator<<(std::ostream& out, const pair& pair) {
        return out << "(" << *pair.key << ", " << *pair.value << ")";
    }


};

template<typename K, typename V>
class map_impl : public clean_base {

    /*
    map is modeled by finite set of Pair
    */

private:

    virtual std::string to_str() = 0;

public:


    /**
     * @brief Adds the pair (key, value) to this
     *
     * @param key - the key to be added
     * @param value - the associated value to be added
     *
     * @requires key is not in DOMAIN(this)
     * @ensures this = #this union {(key, value)}
     */
    virtual void add(K&& key, V&& value) = 0;


    /**
     * @brief Reports whether there is a pair in this whose first component is key
     *
     * @param key - the key to be checked
     * @return true iff there is a pair in this whose first component is key
     * @ensures hasKey = (key is in DOMAIN(this))
     */
    virtual bool hasKey(K&& key) = 0;


    /**
     * @brief Removes the pair whose first component is key and returns it
     *
     * @param key - the key to be removed
     * @return the pair removed
     * @requires key is in DOMAIN(this)
     * @ensures remove.key = key and remove is in #this and this = #this \ {remove}
     */
    virtual pair<K, V> remove(K&& key) = 0;


    /**
     * @brief Removes and returns an arbitrary pair from this
     *
     * @return the pair removed from this
     * @requires |this| > 0
     * @ensures removeAny is in #this and this = #this \ {removeAny}
     */
    virtual pair<K, V> removeAny() = 0;


    /**
     * @brief Reports the size of this
     *
     * @return the number of pairs in this
     * @ensures size = |this|
     */
    virtual int size() = 0;

    friend std::ostream& operator<<(std::ostream& out, map_impl<K, V>& o) {
        return out << o.to_str();
    }

};

}

#endif /* clean_map_h */