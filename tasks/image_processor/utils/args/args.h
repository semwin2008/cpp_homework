#pragma once

#include <string>
#include <vector>


class FilterArgs {
public:
    FilterArgs() = default;
    FilterArgs(std::string arg) : args_(std::vector<std::string>(1, arg)) {}
    std::string operator[](const size_t index) const {
        return args_[index];
    }
    std::string& operator[](const size_t index) {
        return args_[index];
    }
    size_t size() const {
        return args_.size();
    }
    void push_back(const std::string& elem) {
        args_.push_back(elem);
    }
private:
    std::vector<std::string> args_;
};

struct InputArgs{
    std::vector<std::pair<std::string, FilterArgs>> filter_args;
    std::string input_file_path;
    std::string output_file_path;
};