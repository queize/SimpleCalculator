#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>

// Проверка строки на число
// Проверка строки на число
bool is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c)
                                      { return !std::isdigit(c); }) == s.end();
}

// Функция, чтобы проверить, является ли символ оператором
bool isoperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Функция, чтобы получить приоритет оператора
int getprecedence(char c)
{
    if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Функция для расчета выражение из строки вида ОПЗ
double CalCulateFromString(const std::string &str)
{
    std::stack<double> stk;
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
            double top_num = stk.top();
            stk.pop();
            double bottom_num = stk.top();
            stk.pop();
            stk.push(bottom_num + top_num);
        }
        else if (check_str == "-")
        {
            double top_num = stk.top();
            stk.pop();
            double bottom_num = stk.top();
            stk.pop();
            stk.push(bottom_num - top_num);
        }
        else if (check_str == "*")
        {
            double top_num = stk.top();
            stk.pop();
            double bottom_num = stk.top();
            stk.pop();
            stk.push(bottom_num * top_num);
        }
        else if (check_str == "/")
        {
            double top_num = stk.top();
            stk.pop();
            double bottom_num = stk.top();
            stk.pop();
            if (top_num == 0)
            {
                throw std::invalid_argument("Division by zero");
            }
            stk.push(bottom_num / top_num);
        }
    }
    return stk.top();
}

// Функция для преобразования выражения Infix в PostFix (обратная польская запись)
std::string infixtopostfix(const std::string &infix)
{
    std::stack<char> operatorstack;
    std::string postfix = "";
    long long number = 0;
    for (int i = 0; i < infix.length(); i++)
    {
        char currentchar = infix[i];

        // Если текущая строка является числом, добавим его в PostFix
        if (isdigit(currentchar))
        {
            number *= 10;
            number += currentchar - '0';
            char next_char = infix[i + 1]; 
            if (!(isdigit(next_char)))
            {
                postfix += std::to_string(number) + ' ';
                number = 0;
            }
        }
        // Если текущий символ является оператором
        else if (isoperator(currentchar))
        {
            // Операторы с более высоким или равным приоритетом из стека
            while (!operatorstack.empty() && getprecedence(currentchar) <= getprecedence(operatorstack.top()))
            {
                postfix += operatorstack.top();
                postfix += ' ';
                operatorstack.pop();
            }
            // Выталкивание текущего оператора на стек
            operatorstack.push(currentchar);
        }

        // Если текущий символ является левой скобкой, то поместим его в стек
        else if (currentchar == '(')
        {
            operatorstack.push(currentchar);
        }

        // Если текущий символ является правой скобкой, операторы выбиваются из стека до тех пор, пока не найдены левая скобка
        else if (currentchar == ')')
        {
            while (!operatorstack.empty() && operatorstack.top() != '(' )
            {
                postfix += operatorstack.top();
                postfix += ' ';
                operatorstack.pop();
            }
            // занять левую скобку
            if (!operatorstack.empty())
            {
                operatorstack.pop();
            }
        }
    }

    // выбить оставшихся операторов из стека
    while (!operatorstack.empty())
    {
        postfix += operatorstack.top();
        postfix += ' ';
        operatorstack.pop();
    }

    return postfix;
}

int main()
{
    while(true)
    {
        try
        {
            std::string str;
            std::getline(std::cin, str);
            str = infixtopostfix(str);
            std::cout << CalCulateFromString(str) << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}