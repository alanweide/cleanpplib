#include <iostream>

using namespace std;


struct integer {
        int min = 5;
} dog;

struct integer foo(struct integer* cat){
    

    return *cat;
}

int main(){

    cout<<foo(&dog).min<<endl;

}