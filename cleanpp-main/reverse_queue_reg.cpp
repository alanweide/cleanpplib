//
//  selection_sort2.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/15/21.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <iostream>
#include <queue>


using namespace std;

template<typename T>
void flip(queue<T>& q){

    if( !q.empty() ){

      T front = q.front();
      q.pop();
      flip<T>( q );
      q.push(front);

    }
}

int main(int argc, const char* argv[]) {
    
    queue<int> q;
    q.push(5);
    q.push(3);
    q.push(4);
    q.push(2);

    flip<int>( q );

    cout<<"Flipped queue: "<<endl;
  
    while( !q.empty() ){
        cout<<q.front()<<endl;
        q.pop();
    }
}
