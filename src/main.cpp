#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>

bool is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c)
                                      { return !std::isdigit(c); }) == s.end();
}

long long CalCulateFromString(const std::string &str)
{
    std::stack<long long> stk;
    stk.push(0);
    std::stringstream ss(str);
    while (ss)
    {
        std::string check_str;
        ss >> check_str;
        if (is_number(check_str))
        {
            stk.push(std::atoi(check_str.data()));
        }
        else if (check_str == "+")
        {
            int top_num = stk.top();
            stk.pop();
            int bottom_num = stk.top();
            stk.pop();
            stk.push(top_num + bottom_num);
        }
        else if (check_str == "-")
        {
            int top_num = stk.top();
            stk.pop();
            int bottom_num = stk.top();
            stk.pop();
            stk.push(top_num - bottom_num);
        }
        else if (check_str == "*")
        {
            int top_num = stk.top();
            stk.pop();
            int bottom_num = stk.top();
            stk.pop();
            stk.push(top_num * bottom_num);
        }
        else if (check_str == "/")
        {
            int top_num = stk.top();
            stk.pop();
            int bottom_num = stk.top();
            stk.pop();
            stk.push(top_num / bottom_num);
        }
    }
    return stk.top();
}

std::string FormatString(const std::string &str)
{
    std::string str_new = str;
    std::stack<std::pair<char, size_t>> stk_chr;
    for(const auto &chr : str)
    {
        if(std::isdigit(chr))
        {
            str_new += chr + ' ';   
        }
        else if(stk_chr.empty())
        {   
            if (chr == '(') stk_chr.push(std::make_pair(chr, 1));
            if (chr == '+' || chr == '-') stk_chr.push(std::make_pair(chr, 2));
            if (chr == '*' || chr == '/') stk_chr.push(std::make_pair(chr, 3))
        }
    }
    return str;
}

int main()
{
    while(true)
    {
        std::string str;
        std::getline(std::cin, str);
        std::cout << CalCulateFromString(str) << '\n';
    }
}