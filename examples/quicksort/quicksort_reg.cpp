//
//  selection_sort_reg.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/2/21.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <iostream>
#include <queue>

using namespace std;

template<typename T>
void partition(queue<T>& q, queue<T>& front, queue<T>& back, T partition){
    while( !q.empty() ){
        T element = q.front();
        q.pop();
        if(partition < element){
            back.push(element);
        } else {
            front.push(element);
        }
    }
}

template<typename T>
void quickSort(queue<T>& q){
    
    if( q.size() > 1 ){
        queue<T> front, back;

        T partitioner = q.front();
        q.pop();

        partition(q, front, back, partitioner);
        
        quickSort(front);
        quickSort(back);
       
       front.push(partitioner);
        while( !back.empty() ){
            front.push(back.front());
            back.pop();   
        }
        
        q = front;
    }

}


int main(int argc, const char* argv[]) {

  queue<int> q;
  
  q.push(2);
  q.push(3);
  q.push(5);
  q.push(4);

  queue<int> front, back;
  
  quickSort<int>(q);

  //print out sorted queue
  std::cout<<"Sorted queue: <"<<std::endl;
  while( q.size() > 1 ){
    cout<<q.front()<<", ";
    q.pop();
  }
  cout<<q.front()<<">"<<endl;

}
