//
//  linked_stack.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef linked_stack_hpp
#define linked_stack_hpp

#include <stdio.h>
#include <clean_stack.hpp>

namespace cleanpp {

template <class T>
class linked_stack: public clean_stack<T> {
private:
    class stack_node: public clean_base<void> {
    private:
    public:
        T contents;
        std::unique_ptr<stack_node> next;
        
        stack_node();
        
        stack_node(stack_node const &other) = delete;
        stack_node(stack_node&& other);
        
        stack_node& operator=(const stack_node& other) = delete;
        stack_node& operator=(stack_node&& other);
        
        stack_node(T& new_contents);
        
        void clear() override {
            contents = T();
            next.reset();
        }
        
        std::ostream& print(std::ostream& out) override {
            return out << contents;
        }
    };
    
    std::unique_ptr<stack_node> top_ptr_;
public:
    linked_stack<T>();
    
    linked_stack<T>(linked_stack<T> const &other) = delete;
    linked_stack<T>(linked_stack<T>&& other);
    
    linked_stack<T>& operator=(const linked_stack<T>& other) = delete;
    linked_stack<T>& operator=(linked_stack<T>&& other);
    
    void clear() override;
    
    void push(T& x) override;
    
    void pop(T& x) override;
    
    bool is_empty() const override;
    
    std::ostream& print(std::ostream& out) override;
};

}

#endif /* linked_stack_hpp */
