#include "RPN.hpp"

RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN &RPN::operator=(const RPN & cpy)
{
    if (this != &cpy)
        *this = cpy;
    return *this;
}

RPN::RPN(const RPN & cpy)
{
    *this = cpy;
}

bool RPN::check_args(char **argv)
{
    std::string str = argv[1];
    std::string::iterator it = str.begin();
    _i = 0;
    if (check_operator(it, str) == 1)
    {
        std::cout << "Error, bad identation in the list" << std::endl;
        return true;
    }
    while (it < str.end())
    {
        int check = check_char(it);
        if (check == 3)
        {
            std::cout << "Error, bad character in the list: " << *it << std::endl;
            return true;
        }
        else if (*it != ' ')
        {
            if (check == 1)
            {
                //mettre nb
                std::string tmp = str.substr(_i, str.length());
                _c = tmp.c_str();
                double nb = atoi(_c);
                _st.push(nb);
            }
            else if (check == 2)
            {
                int nb1 = _st.top();
                _st.pop();
                int nb2 = _st.top();
                _st.pop();
                if (*it == '+')
                     nb2 = nb2 + nb1;
                else if (*it == '-')
                    nb2 = nb2 - nb1;
                else if (*it == '/')
                {
                    if (nb1 == 0)
                    {
                        nb2 = nb2 + 0;
                        std::cout << "error with 0" << std::endl;
                        return 1;
                    }
                    else
                        nb2 = nb2 / nb1;
                }
                else if (*it == '*')
                    nb2 = nb2 * nb1;
                _st.push(nb2);
            }
        }
        it++;
        _i++;
    }
    std::cout << _st.top() << std::endl;
    return false;
}

int RPN::check_char(std::string::iterator it)
{
    if (*it >= 48 && *it <= 57)
        return 1;
    else if (*it == '*' || *it == '+'
            || *it == '/' || *it == '-'
            || *it == ' ')
        return 2;
    return 3;
}

// check -> si doublon + si si ca fais nb puis signe
//corriger multi nombre, multi signe

bool RPN::check_operator(std::string::iterator it, std::string str)
{
    std::string::iterator it_tmp = it;
    int check = -1;
    int check2 = -1;
    int check3 = -1;
    int cpt_op = 0;
    int cpt_nb = 1;
    if (isdigit(str[0]) == 0 || isdigit(str[2]) == 0 || check_char(it + 4) != 2)
        return 1;
    size_t i = 0;
    it_tmp += 5;
    while (i < str.size() - 5)
    {
        check = check_char(it_tmp);
        if (*it_tmp == ' ')
            check = 4;
        if ((check == check2 && check2 != -1) || (check2 == check3 && check3 != -1))
            return 1;
        if (*it_tmp >= 48 && *it_tmp <= 57)
            cpt_nb++;
        else if (*it_tmp == '*' || *it_tmp == '+'
            || *it_tmp == '/' || *it_tmp == '-')
            cpt_op++;
        it_tmp++;
        i++;
        check3 = check2;
        check2 = check;
    }
    if (cpt_nb - cpt_op != 1)
        return 1;
    return 0;
}
