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

    queue<int> temp;
    cout<<"Original queue: "<<endl;
    while(!q.empty()){
        int element = q.front();
        q.pop();
        cout<<element<<endl;
        temp.push(element);
    }
    q = temp;

    flip<int>(q);

    cout<<"Flipped queue: "<<endl;
    while( !q.empty() ){
        cout<<q.front()<<endl;
        q.pop();
    }
}
