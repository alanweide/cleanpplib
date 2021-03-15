//
//  flexible_list.hpp
//  Cleanpp
//
//  Created by Alan Weide on 8/14/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef flexible_list_h
#define flexible_list_h

#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <sstream>
#include "clean_base.hpp"
#include "list_impl.hpp"
#include "stack_based_list.hpp"

namespace cleanpp {

template<typename Item>
class list_kernel: public clean_base {
protected:
    template <typename I>
    using _flex_list_def_t = stack_based_list<I>;
    static_assert(std::is_base_of<list_impl<int>, _flex_list_def_t<int>>::value,
                  "_flex_list_def_t must derive from list<Item>");
    
    std::unique_ptr<list_kernel_impl<Item>> rep_;
    /*
     list_kernel is modeled by (prec: string of T, rem:  string of T)
     */
public:
    
    /*
     initialization ensures this = (<>, <>)
     */
    list_kernel(): rep_(std::make_unique<_flex_list_def_t<Item>>()) {
    }
    
    /*
     initialization ensures this = (<>, <>)
     */
    template <template<typename> class I>
    list_kernel(__attribute__((unused)) const I<Item>& impl): rep_(std::make_unique<I<Item>>()) {
        static_assert(std::is_base_of<list_kernel_impl<Item>, I<Item>>::value,
                      "Type of impl must derive from list_kernel<Item>");
    }
    
    list_kernel(const list_kernel<Item>& other) = delete;
    /*
     clears other
     initialization ensures this = #other
     */
    list_kernel(list_kernel<Item>&& other): rep_(std::move(other.rep_)) {
        other.rep_ = std::make_unique<_flex_list_def_t<Item>>();
    }
    
    list_kernel<Item>& operator=(const list_kernel<Item>& other) = delete;
    
    /*
     clears other
     ensures this = #other
     */
    list_kernel<Item>& operator=(list_kernel<Item>&& other) {
        if (&other == this) {
            return *this;
        }
        rep_ = std::move(other.rep_);
        other.rep_ = std::make_unique<_flex_list_def_t<Item>>();
        return *this;
    }
    
    void clear() override {
        this->rep_->clear();
    }
    
    /*
     updates  this
     requires |this.rem| > 0
     ensures  #this = (this.prec * this.rem[0, 1), this.rem[1, |this.rem|))
     */
    void advance() {
        this->rep_->advance();
    }
    
    /*
     updates   this
     requires |this.prec| > 0
     ensures  this = (#this.prec * #this.rem[0, 1), #this.rem[1, |#this.rem|))
     */
    void retreat() {
        this->rep_->retreat();
    }
    
    /*
     updates this
     clears  x
     ensures this = (#this.prec * <x>, #this.rem)
     */
    void insert(Item&& x) {
        this->rep_->insert(std::forward<Item>(x));
    }
    
    /*
     updates  this
     ensures  #this = (this.prec * <remove>, this.rem)
     */
    Item remove() {
        return this->rep_->remove();
    }
    
    /*
     ensures is_at_end = (|this.rem| = 0)
     */
    bool is_at_end() const {
        return this->rep_->is_at_end();
    }
    
    /*
     ensures is_at_front = (|this.prec| = 0)
     */
    bool is_at_front() const {
        return this->rep_->is_at_front();
    }
    
    std::string to_str() {
        return this->rep_->to_str();
    }
    
    bool operator==(list_kernel<Item> &other) {
        return *this->rep_ == *other.rep_;
    }
    
    friend std::ostream& operator<<(std::ostream& out, list_kernel<Item>& o) {
        return out << *o.rep_;
    }
};

template<typename Item>
class list: public list_kernel<Item> {
public:
    /*
     initialization ensures this = (<>, <>)
     */
    template <template<typename> class I>
    list(__attribute__((unused)) const I<Item>& impl): list_kernel<Item>(impl) {
        static_assert(std::is_base_of<list_impl<Item>, I<Item>>::value,
                      "Type of impl must derive from list<Item>");
    }
    
    /*
     updates this
     ensures this = (<>, #this.prec * #this.rem)
     */
    void reset() {
        std::unique_ptr<list_impl<Item>> casted(static_cast<list_impl<Item>*>(this->rep_.release()));
        
        casted->reset();
        
        this->rep_ = std::move(casted);
    }
};
}


#endif /* flexible_list_h */
