// clean_map.hpp
// Move Semantics

#ifndef clean_map_h
#define clean_map_h


#include <stdio.h>
#include <iostream>
#include <memory>

#include "clean_base.hpp"

namespace cleanpp {

    template <typename K, typename V>
    class pair: public clean_base{
    private:

        std::unique_ptr<K> key;
        std::unique_ptr<V> value;
    public:

        pair(): key(), value() {}

        pair(K&& key, V&& value){
            this->key = std::make_unique<K>(std::move(key));
            this->value = std::make_unique<V>(std::move(value));
        }

        pair(pair const &other) = delete;
        pair(pair&& other):
        key(std::move(other.key)),
        value(std::move(other.value)){
            other.clear();
        }

        pair& operator=(const pair& other) = delete;

        pair& operator=(pair&& other){
            if(&other == this){
                return *this;
            }

            key = std::move(other.key);
            value = std::move(other.value);
            other.clear();
            return *this;
        }

        void clear(){
            key.reset();
            value.reset();
        }

        V getValue(K&& key){
            return std::move(*this->value);
        }

        bool operator==(pair& other){
            return *this->key == *other.key;
        }

        bool operator==(K& key){
            return *this->key == key;
        }

        friend std::ostream& operator<<(std::ostream& out, const pair& pair){
            return out << "(" << *pair.key << ", " << *pair.value << ")";
        }


};

template<typename K, typename V>
class map_impl : public clean_base{

    /*
    map is modeled by finite set of Pair
    */

private:

    virtual std::string to_str() = 0;

public:

    virtual void add(K&& key, V&& value) = 0;

    virtual bool hasKey(K&& key) = 0;

    virtual pair<K, V> remove(K&& key) = 0;

    virtual pair<K, V> removeAny() = 0;

    virtual int size() = 0;

    virtual V value(K&& key) = 0;

    



    friend std::ostream& operator<<(std::ostream& out, map_impl<K, V>& o){
        return out << o.to_str();
    }

};

}

#endif /* clean_map_h */