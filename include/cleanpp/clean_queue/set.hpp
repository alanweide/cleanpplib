#ifndef set_h
#define set_h


#include <stdio.h>
#include <iostream>
#include <memory>

#include "clean_base.hpp"
#include "set_impl.hpp"
#include "set_on_queue.hpp"


namespace cleanpp {

template <typename I>
using _set_def_t = set_on_queue<I>;

template <typename Item>
class set: public clean_base {

    /*
    set is modeled by finite set of Item
    */

   protected:
            std::unique_ptr<set_impl<Item>> rep_;

    public:

        /*
            ensures this = {}
        */
       set(): rep_(std::make_unique<_queue_def_t<Item>>()){
       }

    //    set(__attribute__((unused)) const I<Item>& impl): rep_(std::make_unique<I<Item>>()){
    //        static_assert(std::is_base_of<set_impl<Item>, I<Item>>::value, 
    //             "Template parameter I must derive from cleanpp::queue");
    //    }

       set(const queue<Item> &o) = delete;

       /*
            clears other
            ensures this = #other
       */
      set(set<Item>&& other): rep_(std::move(other.rep_)){
          other.rep_ = std::make_unique<_set_def_t<Item>>();
      }

      set<Item>& operator=(const set<Item>& other) = delete;

      /*
            clears other
            ensures this = #other
      */
     set<Item>& operator=(set<Item>&& other){
         if(&other == this){
             return *this;
         }
         rep_ = std::move(other.rep_);
         other.rep_ = std::make_unique<_set_def_t<Item>>();
         return *this;
     }

     /*
     clears this
     */
    void clear(){
        this->rep_->clear();
    }

    /*
    updates this
    clears x
    ensures this = #this union {x};
    */
   void add(Item&& x){
       rep_->add(std::forward<Item>(x));
   }

    Item remove(Item&& x) {
        return rep_->remove(std::forward<Item>(x));
    }

    Item removeAny(){
        return rep_->removeAny();
    }

    bool contains(Item&& x){
        return rep_->contains(std::forward<Item>(x));
    }

    int getSize(){
        return rep_->getSize();
    }



};


}

#endif /* set_h */