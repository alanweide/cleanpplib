#include <iostream>
#include <queue>

using namespace std;

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
  
  int min = removeMin<int>(q);

  cout<<"Minimum element is: ";
  cout<<min<<endl<<endl;
  
  sort<int>(q);

  cout<<"Sorted rest of queue: (left to right) "<<endl;
  cout<<"<";
  while( q.size() > 1 ){
  
    cout<<q.front()<<", ";
    q.pop();
  
  }
  cout<<q.front()<<">"<<endl;

}
