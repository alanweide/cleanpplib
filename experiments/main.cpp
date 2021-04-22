#include <stdio.h>
#include <clean_nn/natural_number.hpp>

int main(int argc, const char* argv[]) {
    cleanpp::natural_number n;
    n.set_from_long(462);
    std::cout << n << std::endl;
    return 0;
}