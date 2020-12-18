#pragma once

#include <variant>
#include <string>
#include <fstream>

namespace balancing_scale {
    struct Node {
        std::variant<size_t, std::string> value_;
        size_t node_weight_{0};
        size_t left_delta_{0};
        size_t right_delta_{0};
        Node *left_{nullptr};
        Node *right_{nullptr};

        explicit Node(std::variant<size_t, std::string> value);

        [[nodiscard]] size_t Get() const;

        [[nodiscard]] std::string GetName() const;
    };

    struct Tree {
        Node *root_{nullptr};

        std::string out_file_name_{"System.out"};

        std::ofstream writer_;

        ~Tree() {
            if(writer_) {
                writer_.close();
            }
        }

        explicit Tree(const std::string &in_file_name);

        Node *GetNode(size_t weight, std::string_view name);

        size_t Balance(Node *root);

        void PrintPreorder(Node *root);
    };
}