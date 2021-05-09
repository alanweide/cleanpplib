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

    stack<int> temp;
    int element;
    cout<<"Original stack (from top to bottom): ";
    cout<<"< ";
    while(s.size() > 1){
        element = s.top();
        s.pop();
        cout<<element<<", ";
        temp.push(element);
    }
    element = s.top();
    s.pop();
    cout<<element<<" >"<<endl;
    temp.push(element);
    s = temp;

    flip<int>(s);

    cout<<"Flipped stack (from top to bottom): ";
    cout<<"< ";
    while(s.size() > 1){
        cout<<s.top()<<", ";
        s.pop();     
    }
    cout<<s.top()<<">"<<endl;
    
 
}
