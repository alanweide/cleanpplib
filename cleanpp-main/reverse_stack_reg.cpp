//
//  selection_sort2.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/15/21.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <iostream>
#include <stack>

using namespace std;

/**
 * Reverses ("flips") {@code this}.
 * 
 *  @param s
 *              the stack
 * @updates s
 * @returns s
 * @ensures s = rev(#s)
 */
template<typename T>
void flip(stack<T>& s){

    stack<T> result;
    
    while( !s.empty() ){

        result.push( s.top() );
        s.pop();

    }
    s = result;
    
}


int main(int argc, const char* argv[]) {
    stack<int> s;

    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    flip<int>(s);

    std::cout<<"Flipped stack (from top to bottom):"<<std::endl;

    while( !s.empty() ){
        cout<<s.top()<<endl;
        s.pop();     
    }
    
 
}
