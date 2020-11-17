#include <memory>

std::unique_ptr<int>&& foo() {
    std::unique_ptr<int> x = std::make_unique<int>(0);
    return std::move(x);
}

int main() {
    std::unique_ptr<int> y = foo();
}