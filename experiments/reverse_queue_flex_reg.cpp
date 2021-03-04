//
//  selection_sort2.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/15/21.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <memory>
#include <iostream>
#include <queue>


using namespace std;

template<typename T>
queue<T> flip(queue<T> q){

    if( !q.empty() ){

      T front = q.front();
      q.pop();
      q = flip<T>( std::move(q) );
      q.push(std::move(front));

      
    }

    return std::move(q);
}



int main(int argc, const char* argv[]) {
    
    queue<int> q;
    q.push(5);
    q.push(3);
    q.push(4);
    q.push(2);

    q = flip<int>( std::move(q) );

    cout<<"Flipped queue (from top to bottom):"<<endl;

  
    while( !q.empty() ){
        cout<<q.front()<<endl;
        q.pop();
    }
}
