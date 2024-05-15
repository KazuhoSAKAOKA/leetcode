#pragma once

#include <string>
#include <vector>
#include <functional>

template <typename T, typename F> 
std::vector<T> get_list(const std::string& data, F convert) {
    size_t index = 0;
    std::vector<T> list;
    const auto col_begin = data.find_first_of('[', index);
    if (col_begin == std::string::npos) {
        list;
    }
    index = col_begin + 1;
    bool is_end = false;
    while (index < data.size() && !is_end) {
        const auto value_end = data.find_first_of(",]", index);
        if (value_end == std::string::npos) {
            throw std::exception();
        }
        is_end = data[value_end] == ']';
        const auto value_str = data.substr(index, value_end - index);
        list.emplace_back(convert(value_str));
        index = value_end + 1;
    }
    return list;
}

template <typename T, typename F>
std::vector<std::vector<T>> get_matrix(const std::string& data, F convert) {
    size_t index = 0;
    const auto data_begin = data.find_first_of('[', index);
    if (data_begin == std::string::npos) {
        throw std::exception();
    }
    index = data_begin + 1;

    std::vector<std::vector<T>> matrix;
    while (index < data.size()) {
        const auto col_begin = data.find_first_of('[', index);
        if (col_begin == std::string::npos) {
            break;
        }
        index = col_begin + 1;
        std::vector<T> cols;
        bool is_end = false;
        while (index < data.size() && !is_end) {
            const auto value_end = data.find_first_of(",]", index);
            if (value_end == std::string::npos) {
                throw std::exception();
            }
            is_end = data[value_end] == ']';
            const auto value_str = data.substr(index, value_end - index);
            cols.emplace_back(convert(value_str));
            index = value_end + 1;
        }
        matrix.emplace_back(cols);
    }

    return matrix;
}



std::vector<int> get_list_int(const std::string& data) {
    return get_list<int>(data, [](const std::string& value) { return std::stoi(value); });
}

std::vector<std::vector<int>> get_matrix_int(const std::string& data) {
    return get_matrix<int>(data, [](const std::string& value) { return std::stoi(value); });
}

std::vector<long long> get_list_ll(const std::string& data) {
    return get_list<long long>(data, [](const std::string& value) { return std::stoll(value); });
}

std::vector<std::vector<long long>> get_matrix_ll(const std::string& data) {
    return get_matrix<long long>(data, [](const std::string& value) { return std::stoll(value); });
}
inline std::string remove_double_quotes(const std::string& value) {
    const auto s = value.find_first_of('"');
    if (s == std::string::npos) { return value; }
    const auto e = value.find_first_of('"', s + 1);
    if (e == std::string::npos) { throw std::exception(); }
    return value.substr(s + 1, e - s - 1);
}
std::vector<std::string> get_list_str(const std::string& data) {
    return get_list<std::string>(data, remove_double_quotes);
}
std::vector<std::vector<std::string>> get_matrix_str(const std::string& data) {
    return get_matrix<std::string>(data, remove_double_quotes);
}
