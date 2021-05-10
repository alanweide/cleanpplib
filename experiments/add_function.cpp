#include <clean_nn/stack_nn.cpp>
#include <clean_nn/natural_number.cpp>
#include <nn_impl/bounded_nn.hpp>
#include <nn_impl/stack_nn.hpp>
#include <nn_impl/nn_impl.hpp>
#include <natural_number.hpp>
#include <iostream>
#include <clean_integer/nn_integer.cpp>
#include <clean_integer/integer_impl.cpp>
#include <integer_impl/nn_integer.hpp>
#include <integer_impl/integer_impl.hpp>
#include <integer.hpp>


using namespace cleanpp;


int main() {


    // natural_number x(71L), y(66L), product;

    // std::tie(product, x, y) = subtract(std::move(x), std::move(y));

    // std::cout<<"Begin main function output:"<<std::endl;
    // std::cout<<product<<std::endl;
    // std::cout<<x<<std::endl;
    // std::cout<<y<<std::endl;
    
    integer x(5L), y(6L), sum;

    std::tie(sum, x, y) = subtract(std::move(x), std::move(y));
    std::cout<<sum<<std::endl;
    std::cout<<x<<std::endl;
    std::cout<<y<<std::endl;

}