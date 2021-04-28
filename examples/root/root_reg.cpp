#include <iostream>

using namespace std;

int power(int n, int p){
    
    int i = 0;
    int base = n; 

    while(i < p - 1){ 
        base *= n;
        i++;
    }

    return base;
}

int root(int n, int r){

    int result;

    if(n == 1){
        result = 1;
    } else {
        int lowEnough = 0;
        int tooHigh = n;
        while( lowEnough + 1 != tooHigh ){

            int root = (lowEnough + tooHigh) / 2;
            int powerResult = power(root, r);

            if( powerResult > n ){
                tooHigh = root;
            }
            else{
                lowEnough = root;
            }
        }
        result = lowEnough;
    }

    return result;
}

int main(int argc, const char * argv[]) {
    
    long int input;
    int r;
    
    while(input != -1){
        std::cout<<"Please enter a number: ";
        std::cin>>input;
        std::cout<<"Please enter the root to take: ";
        std::cin>>r;

        std::cout<<"result of root is: "<<std::endl;
        std::cout<<root(input, r)<<std::endl;

    }
}
