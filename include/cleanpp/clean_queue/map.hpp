#ifndef set_h
#define set_h


#include <stdio.h>
#include <iostream>
#include <memory>

#include "clean_base.hpp"
#include "set_impl.hpp"
#include "set_on_queue.hpp"



namespace cleanpp {

template <typename K, typename V>
using _map_def_t = map_on_set<K, V>;

template <typename K, typename V>
class map: public clean_base {

    /*
        map is modeled by finite set of pair
    */

   protected:
            std::unique_ptr<map_impl<K, V>> rep_;

    public:

        /*
            ensures this = {}
        */
       map(): rep_(std::make_unique<_map_def_t<K, V>>()){
       }

       template<template<typename> class I>
       map(__attribute__((unused)) const I<K, V>& impl): rep_(std::make_unique<I<K, V>>()){
           static_assert(std::is_base_of<map_impl<K, V>, I<K, V>>::value,
                "Template parameter I must derive from cleanpp::set");
       }

       map(const map<K, V> &o) = delete;

    
       /*
            clears other
            ensures this = #other
       */
      map(map<K, V>&& other): rep_(std::move(other.rep_)){
          other.rep_ = std::make_unique<_map_def_t<K, V>>();
      }

      map<K, V>& operator=(const map<K, V>& other) = delete;

      /*
        clears other
        ensures this = #other
      */
     map<K, V>& operator=(map<K, V> && other){
         if(&other == this){
             return *this;
         }
        rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_map_def_t<K, V>>():
        return *this;
     }

     /*
        clears this
     */
    void clear(){
        this->rep_->clear();
    }

    void add(pair&& x){
        this->rep_->add(x);
    }

    bool hasKey(K&& key){
        return this->rep_->hasKey(key);
    }

    pair remove(pair&& x){
        return this->rep_->remove(std::forward<pair>(x));
    }

    pair removeAny(){
        return this->rep_->removeAny();
    }

    int size(){
        return this->rep_->size();
    }

    friend std::ostream& operator<<(std::ostream& out, map<Item>& o){
        return out << *o.rep_;
    }


};


}

#endif /* map_h */

