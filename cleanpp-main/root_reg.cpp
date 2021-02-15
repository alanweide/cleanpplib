//
//  main.cpp
//  cleanpp-main
//
//  Created by Alan Weide on 10/2/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <iostream>

using namespace std;

int power(int n, int p){
    
    int i = 0;
    int base = 1; 

    while(i < p){ 
        base *= n;
        i++;
    }

    return base;
}

int root(int n, int r){

    int result;
    int lowEnough = 0;
    int tooHigh = n;

    int root = 0;

    while( lowEnough + 1 != tooHigh ){

        root = (lowEnough + tooHigh) / 2;

        int powerResult = power(root, r);
        cout<<root<<" to the power of "<<r<<" is "<<powerResult<<endl;

        if( powerResult > n ){
            tooHigh = root;
        }
        else{
            lowEnough = root;
        }
    }
    if(n != 1){
        result = lowEnough;
    } else{
        result = tooHigh;
    }

    return result;
}

int main(int argc, const char * argv[]) {
    
    
    long unsigned int input;
    int r;
    
    while(input != -1){
        int n;
        std::cout<<"Please enter a number: ";
        std::cin>>n;
        std::cout<<"Please enter the root to take: ";
        std::cin>>r;

        std::cout<<"result of root is: "<<std::endl;
        std::cout<<root(n, r)<<std::endl;

    }
}
