//
//  clean_set.hpp
//  Move Semantics



#ifndef clean_set_h
#define clean_set_h

#include <stdio.h>
#include <iostream>
#include <memory>

#include "clean_base.hpp"

namespace cleanpp {

template<typename T> 
class set_impl : public clean_base {

    /*
    set is modeled by finite set of T
    */   
private:
    // virtual std::string to_str() = 0;
public:
    
    /**
     * Adds x to this
     * parameter: x - the element to be added
     * aliases reference x
     * updates this
     * requires: x is not in this
     * ensures this = #this union {x}
     * 
    **/
   virtual void add(T&& s) = 0;

   /**
    * Removes x from this, and returns it.
    * parameter: x - the element to be removed
    * returns: the element removed
    * updates: this
    * requires: x is in this
    * ensures: this = #this \ {x} and remove = x
    **/
   virtual T remove(T&& x) = 0;

    /**
     * Removes and returns an arbitrary element from this
     * 
     * returns: the element removed from this
     * updates; this
     * requires: |this| > 0
     * ensures: removeAny is in #this and this = #this \ {removeAny}
     **/
    virtual T removeAny() = 0;

    /**
     * Reports whether x is in this.
     * parameter: x - the element to be checked
     * returns: true iff element is in this
     * ensures: contains = (x is in this)
     **/
    virtual bool contains(T&& x) = 0;

    /**
     * Reports size (cardinality) of this.
     * returns: the number of elements in this
     * ensures: size = |this|
     **/
    virtual int getSize() = 0;

    friend std::ostream& operator<<(std::ostream& out, set_impl<T> & o){
         return out << o.to_str();
    }

    

};


}

#endif /* clean_set_h */