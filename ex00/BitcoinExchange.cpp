#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::~BitcoinExchange()
{
    
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange & copy)
{
    *this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange & copy)
{
    if (this != &copy)
        *this = copy;
    return *this;
}

bool BitcoinExchange::check_file(char **argv)
{
    std::ifstream file(argv[1]);
    std::string str;
    if (fill_container() == 1)
        return 1;
    if (!file.is_open())
    {
        std::cout << "Error: could not open the file" << std::endl;
        return false;
    }
    getline(file, str, '\n');
    if (str != "date | value")
    {
        std::cout << "first line should be: date | value " << std::endl;
        return false;
    }
    // suel charac a autoriser: ' ', '|', '-', 'nombre', '\n'
    if (check_charac(file, str) == 1)
        return false;
    for (; file.eof() != 1;)
    {
        getline(file, str, '\n');
        verify_line(str);
    }
    return true;
}

bool BitcoinExchange::check_charac(std::ifstream file, std::string str)
{
    
    std::cout << "voici la str" << str << std::endl;
    for (; file.eof() != 1;)
    {
        getline(file, str, '\n');
    }
    return 0;
}

bool BitcoinExchange::fill_container()
{
    std::string data;
    std::string tmp;
    std::ifstream file("data.csv");
    if (!file.is_open())
    {
        std::cout << "Error: could not open the data.csv" << std::endl;
        return false;
    }
    getline(file, data, '\n');
    for(;file.eof() != 1;)
    {
        getline(file, data, '\n');
        if (data.length() == 0)
            break;
        tmp = data.substr(0, 10);
        int len = data.length() - tmp.length();
        float nb;
        std::string buf = data.substr(11, len);
        nb = std::atof(buf.c_str());
        this->_ma[tmp] = nb;
    }
    return false;
}

bool BitcoinExchange::verify_line(std::string str)
{
    char buf1[4];
    double tmp[4];
    str.copy(buf1, 4, 0);
    try
    {
        tmp[0] = atoi(buf1);
    }
    catch(const std::exception & e)
    {
        std::cout << "Error: bad input => " << tmp[0] << std::endl;
        return true;
    }
    if (tmp[0] > 2147483648)
        return true;
    for (int i = 0; buf1[i]; i++)
        buf1[i] = 0;
    str.copy(buf1, 2, 5);
    for (int i = 0; i < 2; i++)
    {
        try
        {
            tmp[i] = atoi(buf1);
            if (tmp[i] > 31 && i == 0)// verif la date
            {
                std::cout << "Error: bad date input => " << tmp[i] << std::endl;
                return true;
            }
            else if (tmp[i] < 0 && i == 0)
            {
                std::cout << "Error: not a positive number => " << tmp[i] << std::endl;
                return true;
            }
            else if (tmp[i] < 0 && i == 1)
            {
                std::cout << "Error: not a positive number => " << tmp[i] << std::endl;
                return true;
            }
            else if (tmp[i] > 12 && i == 1)
            {
                std::cout << "Error: bad month input => " << tmp[i] << std::endl;
                return true;
            }
        }
        catch(const std::exception & e)
        {
            std::cout << "Error, wrong date" << std::endl;
            return true;
        }
        for (int i = 0; buf1[i]; i++)
            buf1[i] = 0;
        str.copy(buf1, 2, 8);
    }
    for (int i = 0; buf1[i]; i++)
        buf1[i] = 0;
    str.copy(buf1, 11, 13);
    try
    {
        tmp[3] = atof(buf1);
        if (tmp[3] > 1000)
        {
            std::cout << "Error: too large number => " << tmp[3] << std::endl;
            return true;
        }
        else if (tmp[3] < 0)
        {
            std::cout << "Error: not a positive number => " << tmp[3] << std::endl;
            return true;
        }
    }
    catch(const std::exception & e)
    {
        std::cout << "Error, wrong value" << std::endl;
        return true;
    }
    execute_line(buf1, tmp, str);
    return false;
}

void BitcoinExchange::execute_line(char *buf, double *tmp, std::string str)
{
    (void)buf;
    (void)tmp;
    std::string wait(str.substr(0, 10));
    if (_ma.find(wait) != _ma.end())
    {
        std::map<std::string, float>::iterator it = _ma.find(wait);
        std::string af = str.substr(0, 10);
        float nb = it->second;
        std::cout << af << " => " << tmp[3] << " = " << nb << std::endl;
    }
    else
    {
        std::map<std::string, float>::iterator it;
        it = _ma.lower_bound(wait);
        it--;
        std::string af = str.substr(0, 10);
        int len = str.length() - 12;
        std::string cpy(str.substr(12, len));
        float nb = it->second;
        float nb2 = std::atof(cpy.c_str());
        float result = nb * nb2;
        std::cout << af << " => " << tmp[3] << " = " << result << std::endl;
    }
}

// lower bond

// fill le container avec les en string, les date puis en valeur double
// 2011-01-03 => 3 = 0.9

// void BitcoinExchange::fill_container(std::string str)
// {
//     // std::cout << "string de base " << str << std::endl;
//     std::string tmp;
//     tmp = str.substr(0, 10);
//     int len = str.length() - tmp.length() - 3;
//     double nb;
//     // je passe a la valeur
//     std::string buf = str.substr(13, len);
//     nb = std::atof(buf.c_str());
//     this->_ma[tmp] = nb;
//     std::cout << tmp << " => " << this->_ma[tmp] << std::endl;
// }
