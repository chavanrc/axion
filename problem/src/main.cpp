#include <balancing_scale.hpp>
#include <iostream>

int32_t main() {
    std::string in_file;
    std::cout << "Enter input file: ";
    std::cin >> in_file;
    balancing_scale::Tree tree(in_file);
    tree.Balance(tree.root_);
    tree.PrintPreorder(tree.root_);
}
