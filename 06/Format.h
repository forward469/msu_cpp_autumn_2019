#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>


template<class T>
std::string to_string(T&& arg)
{
    std::ostringstream stream;
    stream << arg;
    return stream.str();
}

template<class... T>
std::string format(const std::string& STR, T&&... args)
{
    std::vector<std::string> args_ = {to_string(std::forward<T>(args))...};
    std::ostringstream result;

    for (size_t i = 0; i < STR.length(); i++){
        if (STR[i] == '}')
            throw std::runtime_error("NOT FOUND: left bound");
		if (STR[i] == '{')
		{
            i++;
            size_t NUM = 0;

            if (STR[i] == '}')
                throw std::runtime_error("NOT FOUND: arguments");

            while ((STR[i] != '}') && (i < STR.length())){
                NUM = 10 * NUM + STR[i] - '0';
                i++;
            }

            if (i >= STR.length())
                throw std::runtime_error("NOT FOUND: right bound");

            if (NUM > args_.size() - 1)
                throw std::runtime_error("WRONG: arguments");

            result << args_[NUM];
            continue;
        }

        result << STR[i];
    }

    return result.str();
}