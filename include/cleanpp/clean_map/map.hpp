#ifndef map_h
#define map_h


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

       template<template<typename, typename> class I>
       map(__attribute__((unused)) const I<K, V>& impl): rep_(std::make_unique<I<K, V>>()){
           static_assert(std::is_base_of<map_impl<K, V>, I<K, V>>::value,
                "Template parameter I must derive from cleanpp::map");
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
        other.rep_ = std::make_unique<_map_def_t<K, V>>();
        return *this;
     }

     /*
        clears this
     */
    void clear(){
        this->rep_->clear();
    }

    void add(K&& key, V&& value){
        
        this->rep_->add(std::move(key), std::move(value));
    }

    pair<K, V> remove(K&& x){
        return this->rep_->remove(std::forward<K>(x));
    }

    pair<K, V> removeAny(){
        return this->rep_->removeAny();
    }

    V value(K&& key){
        return this->rep_->value(std::move(key));
    }

    bool hasKey(K&& key){
        return this->rep_->hasKey(std::move(key));
    }

    int size(){
        return this->rep_->size();
    }

    friend std::ostream& operator<<(std::ostream& out, map<K, V>& o){
        return out << *o.rep_;
    }


};


}

#endif /* map_h */

