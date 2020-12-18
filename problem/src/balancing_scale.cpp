#include <balancing_scale.hpp>
#include <iostream>
#include <vector>
#include <sstream>

namespace balancing_scale {
    Node::Node(std::variant<size_t, std::string> value) : value_{std::move(value)} {
    }

    size_t Node::Get() const {
        if (!std::get_if<std::string>(&value_)) {
            return std::get<size_t>(value_);
        }
        return 0;
    }

    std::string Node::GetName() const {
        if (!std::get_if<size_t>(&value_)) {
            return std::get<std::string>(value_);
        }
        return {};
    }

    Tree::Tree(const std::string &in_file_name) {
        std::ifstream reader(in_file_name);
        if (!reader) {
            std::string err = "Error opening input file: " + in_file_name;
            std::cerr << err << std::endl;
            throw std::runtime_error(err);
        }
        std::string line;
        std::vector<std::vector<std::string>> tokens{};
        for (int32_t i = 0; !reader.eof(); i++) {
            getline(reader, line);
            if (!isalpha(line[0])) {
                continue;
            }
            std::istringstream buf(line);
            std::vector<std::string> row;
            for (std::string token; getline(buf, token, ',');) {
                row.emplace_back(token);
            }
            tokens.emplace_back(row);
        }
        Node *root{nullptr};
        for (const auto &row : tokens) {
            int16_t column{0};
            for (const auto &token : row) {
                size_t weight{0};
                std::string name{};

                if (isalpha(token[0])) {
                    name = token;
                } else {
                    weight = std::stoi(token);
                }

                if (!root) {
                    root = GetNode(weight, name);
                    root_ = root;
                } else if (column == 1 && !root->left_) {
                    root->left_ = GetNode(weight, name);
                } else if (column == 2 && !root->right_) {
                    root->right_ = GetNode(weight, name);
                }
                ++column;
            }
            if (root && root->left_ && root->left_->GetName().empty()) {
                root = root->right_;
            } else if (root && root->right_ && root->right_->GetName().empty()) {
                root = root->left_;
            }
        }
        reader.close();
        writer_.open(out_file_name_, std::ios::trunc);
        if (!writer_) {
            std::string err = "Error opening output file: " + out_file_name_;
            std::cerr << err << std::endl;
        }
    }

    Node *Tree::GetNode(size_t weight, std::string_view name) {
        Node *new_node{nullptr};
        if (name.empty() && weight > 0) {
            new_node = new Node(weight);
        } else if (!name.empty() && weight == 0) {
            new_node = new Node(name.data());
        } else if (name.empty() && weight == 0) {
            std::cerr << "Empty name and 0 weight\n";
        }
        return new_node;
    }

    size_t Tree::Balance(Node *root) {
        if (!root) {
            return 0;
        }
        if (root->left_ && root->right_) {
            auto left = root->left_->Get();
            auto right = root->right_->Get();
            if (left == 0) {
                left = Balance(root->left_);
            }
            if (right == 0) {
                right = Balance(root->right_);
            }
            if (left > right) {
                root->right_delta_ = left - right;
            } else if (left < right) {
                root->left_delta_ = right - left;
            }
            root->node_weight_ = root->right_delta_ + root->left_delta_ + left + right + 1;
            return root->node_weight_;
        }
        return 0;
    }

    void Tree::PrintPreorder(Node *root) {
        if (!root) {
            return;
        }
        auto name{root->GetName()};
        if (!name.empty()) {
            if (writer_) {
                writer_ << name << ',' << root->left_delta_ << ',' << root->right_delta_ << '\n';
            } else {
                std::cout << name << ',' << root->left_delta_ << ',' << root->right_delta_ << '\n';
            }
        }
        PrintPreorder(root->left_);
        PrintPreorder(root->right_);
    }

    void Tree::Clean(Node *root) {
        if (!root) {
            return;
        }
        Clean(root->left_);
        Clean(root->right_);
        delete root;
    }
}