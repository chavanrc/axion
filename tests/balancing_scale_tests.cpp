#include <catch2/catch.hpp>
#include <balancing_scale.hpp>
#include <iostream>

TEST_CASE("balancing scale test", "[unit]") {
    /*balancing_scale::Tree tree;

    auto root = tree.GetNode(0, "B1");
    root->left_ = tree.GetNode(10, "");
    root->right_ = tree.GetNode(0, "B2");

    root->right_->left_ = tree.GetNode(0, "B3");
    root->right_->right_ = tree.GetNode(4, "");

    root->right_->left_->left_ = tree.GetNode(7, "");
    root->right_->left_->right_ = tree.GetNode(8, "");

    auto value = tree.Balance(root);

    REQUIRE(value == 71);*/
}

TEST_CASE("balancing scale file test", "[unit]") {
    balancing_scale::Tree tree("../../tests/System.in");
    tree.Balance(tree.root_);
    tree.PrintPreorder(tree.root_);
}