#ifndef map_h
#define map_h


#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>
#include <map_impl/map_on_set.hpp>
#include <set_impl/set_impl.hpp>
#include <set_impl/set_on_queue.hpp>



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

       /**
        * @brief no argument constructor
        * 
        * @ensures this = {}
        */
       map(): rep_(std::make_unique<_map_def_t<K, V>>()){
       }

       template<template<typename, typename> class I>
       map(__attribute__((unused)) const I<K, V>& impl): rep_(std::make_unique<I<K, V>>()){
           static_assert(std::is_base_of<map_impl<K, V>, I<K, V>>::value,
                "Template parameter I must derive from cleanpp::map");
       }

       map(const map<K, V> &o) = delete;

      
      /**
       * @brief Custom move constructor
       * 
       * @param other - the map being moved from
       */
      map(map<K, V>&& other): rep_(std::move(other.rep_)){
          other.rep_ = std::make_unique<_map_def_t<K, V>>();
      }


      map<K, V>& operator=(const map<K, V>& other) = delete;


     /**
      * @brief custom move assignment operator
      * 
      * @param other - the map being moved from
      * @return the newly-assigned this 
      * @ensures this = #other
      */
     map<K, V>& operator=(map<K, V> && other){
         if(&other == this){
             return *this;
         }
        rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_map_def_t<K, V>>();
        return *this;
     }


    /**
     * @brief clears this
     */
    void clear(){
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
    void add(K&& key, V&& value){
        
        this->rep_->add(std::move(key), std::move(value));
    }


    /**
     * @brief Reports whether there is a pair in this whose first component is key
     * 
     * @param key - the key to be checked
     * @return true iff there is a pair in this whose first component is key
     * @ensures hasKey = (key is in DOMAIN(this))
     */
    bool hasKey(K&& key){
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
    pair<K, V> remove(K&& key){
        return this->rep_->remove(std::forward<K>(key));
    }

   
    /**
     * @brief Removes and returns an arbitrary pair from this
     * 
     * @return the pair removed from this
     * @requires |this| > 0
     * @ensures removeAny is in #this and this = #this \ {removeAny}
     */
    pair<K, V> removeAny(){
        return this->rep_->removeAny();
    }


    /**
     * @brief Reports the size of this
     * 
     * @return the number of pairs in this
     * @ensures size = |this|
     */
    int size(){
        return this->rep_->size();
    }

    friend std::ostream& operator<<(std::ostream& out, map<K, V>& o){
        return out << *o.rep_;
    }


};


}

#endif /* map_h */

