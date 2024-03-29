//
//  clean_set.hpp
//  Move Semantics



#ifndef clean_set_h
#define clean_set_h

#include <stdio.h>
#include <iostream>
#include <memory>

#include <clean_base.hpp>
#include "set_on_queue.hpp"


namespace cleanpp
{

template<typename T>
class set_kernel_impl : public clean_base {

  /**
   * set is modeled by finite set of T
   */
private:
  virtual std::string to_str() = 0;
public:


  /**
   * @brief Adds x to this
   *
   * @param x the element to be added
   * @requires x is not in this
   * @ensures this = #this union {x}
   *
   */
  virtual void add(T&& x) = 0;


  /**
   * @brief Reports whether x is in this.
   *
   * @param x - the element to be checked
   * @return true iff element is in this
   * @ensures contains = (x is in this)
   */
  virtual std::tuple<bool, T> contains(T&& x) = 0;


  /**
   * @brief Removes x from this, and returns it.
   *
   * @param x
   * @return the element removed
   * @requires x is in this
   * @ensures \f$ this = \#this \\ \{x\} \f$ and remove = x
   */
  virtual T remove(T&& x) = 0;


  /**
    * @brief Removes and returns an arbitrary element from this
    *
    * @return the element removed fromt this
    * @requires |this| > 0
    * @ensures removeAny is in #this and this = #this \ {removeAny}
    */
  virtual T removeAny() = 0;


  /**
   * @brief Reports size (cardinality) of this
   *
   * @return the number of elements in this
   * @ensures getSize = |this|
   */
  virtual int getSize() = 0;

  virtual bool isEmpty() = 0;

  friend std::ostream& operator<<(std::ostream& out, set_kernel_impl<T>& o) {
    return out << o.to_str();
  }

};

template<typename T>
class set_on_queue;

template<typename T>
class set_impl : public set_kernel_impl<T> {
public:
  /*
   clears s
   updates this
   ensures this = #this union #s 
  */
  std::unique_ptr<set_impl> set_union(std::unique_ptr<set_impl> s){
    std::unique_ptr<set_impl> temp = std::make_unique<set_on_queue<T>>();
    while(!s->isEmpty()){
      T element = s->removeAny();
      bool has;
      std::tie(has, element) = this->contains(std::move(element));
      if(!has) {
        this->add(std::move(element));
      } else {
        temp->add(std::move(element));
      }
    }
    return std::move(temp);
  }
};

}

#endif /* clean_set_h */
