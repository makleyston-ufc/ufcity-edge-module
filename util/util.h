//
// Created by makleyston on 22/09/22.
//

#ifndef UFCITY_UTIL_H
#define UFCITY_UTIL_H

#include <iostream>
#include <string>
#include <algorithm>

const std::string WHITESPACE = " \n\r\t\f\v/";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

#endif //UFCITY_UTIL_H
