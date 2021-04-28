#include <memory>
#include <iostream>

std::unique_ptr<int>&& foo(std::unique_ptr<int>&& y) {
    std::unique_ptr<int> x = std::forward<std::unique_ptr<int>>(y);
    return std::move(x);
}

int main() {
    std::unique_ptr<int> y = std::make_unique<int>(5);
    y = foo(std::move(y));
    std::cout << "y = " << *y << "\n";
}
