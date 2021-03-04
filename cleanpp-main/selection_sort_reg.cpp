//
//  selection_sort3.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/2/21.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <iostream>
#include <queue>

using namespace std;

/**
 * Removes and returns the minimum value from {@code q}.
 * 
 * @param q
 *            the queue
 * @return the minimum value from {@code q} and the updated {@code q}
 * @updates q
 * @requires <pre>
 * q /= empty_string
 * </pre>
 * @ensures <pre>
 * perms(q * <removeMin>, #q)  and
 *  for all x: template type
 *      where (x is in entries (q))
 *    ( <removeMin> <= x )
 * </pre>
 */
template<typename T>
T removeMin(queue<T>& q) {

    T min = q.front();
    q.pop();
    queue<T> temp;
    
    while(!q.empty()){
      T element = q.front();
      q.pop();

      if(element < min){
        
        temp.push(min);
        min = element;

      } else{
        temp.push(element);
      }
    }
    
    q = temp;
    return min; 
}


/**
 * Sorts {@code q}.
 * 
 * @param q
 *            the queue
 * @updates q
 * @ensures q = [#q in nondecreasing order]
 */
template<typename T>
void sort(queue<T>& q){
    
    queue<T> result;

    while(!q.empty()){
        
        T min = removeMin<T>(q);
    
        result.push(min);

    }
    

    q = std::move(result);

}


int main(int argc, const char* argv[]) {

  queue<int> q;
  
  q.push(2);
  q.push(3);
  q.push(5);
  q.push(4);
  
  // struct minAndQueue<stack_nn> result = removeMin<stack_nn>(std::move(qnn)); 
  // qnn = std::move(result.q);
  int min = removeMin<int>(q);


  std::cout<<"Minimum element is: ";
  // std::cout<<toInt(std::move(result.min))<<std::endl<<std::endl;
  cout<<min<<endl<<endl;
  
  sort<int>(q);

  std::cout<<"Sorted rest of queue: (left to right) "<<std::endl;
  
  while( !q.empty() ){
  
    cout<<q.front()<<", ";
    q.pop();
  
  }
  cout<<endl;

}
