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
    std::ifstream file2(argv[1]);
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
    // seul charac a autoriser: ' ', '|', '-', 'nombre', '\n'
    for (; file.eof() != 1;)
    {
        getline(file, str, '\n');
        verify_line(str);
    }
    return true;
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

// a | a
//corriger les -inf et les overflow

bool BitcoinExchange::verify_line(std::string str)
{
    char buf1[4];
    double tmp[4];
    if (str.size() == 0)
    {
        std::cout << "Error: empty line" << std::endl;
        return 1;
    }
    else
    {
        int nb = str.size();
        int i = 0;
        while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f') && str[i])
            i++;
        if (i == nb)
        {
            std::cout << "your line does not respect the form" << std::endl;
            return 1;
        }
    }
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
    int i = 0;
    if (str[4] != '-' || str[7] != '-')
    {
        std::cout << "bad input, miss - or there is not only digit in your date" << std::endl;
        return 1; 
    }
    while (str[i] && i < 10)
    {
        if (i == 4 || i == 7)
            i++;
        if (str[i] < 48 || str[i] > 57)
        {
            std::cout << "there not only digit in your date" << std::endl;
            return 1;
        }
        i++;
    }
    i = 13;
    if (str[12] != ' ')
    {
        std::cout << "a | is missing between date and value or you put too mutch space" << std::endl;
        return 1;
    }
    for (int cpt = 0; str[i]; i++)
    {
        if (str[i] == '.')
            cpt++;
        if (cpt == 2)
        {
            std::cout << "too many dot in your input" << std::endl;
            return 1;
        }
        if ((str[i] < 48 || str[i] > 57) && str[i] != '.')
        {
            std::cout << "there not only digit in your value" << std::endl;
            return 1;
        }
    }
    //check si espace
    for (int i = 0; i < 2; i++)
    {
        try
        {
            tmp[i] = atoi(buf1);
            if (tmp[i] > 12 && i == 0)// verif la date
            {
                std::cout << "Error: bad month input => " << tmp[i] << std::endl;
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
            else if (tmp[i] > 31 && i == 1)
            {
                std::cout << "Error: date month input => " << tmp[i] << std::endl;
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
    // std::cout << "=====" << std::endl << "voici les infos que j'ai recup " << buf1 << " !!! " << tmp << " !!! " << str << std::endl;
    execute_line(buf1, tmp, str);
    return false;
}

void BitcoinExchange::execute_line(char *buf, double *tmp, std::string str)
{
    (void)buf;
    (void)tmp;
    std::string wait(str.substr(0, 10));
    if (wait.empty())
        return ;
    // copier ma date et voir si elle est inf a la date minimal ou maximal
    std::string bel1 = str.substr(0, 4);
    std::string bel2 = str.substr(5, 2);
    std::string bel3 = str.substr(8, 2);
    // std::cout << "voici bel" << bel1 << std::endl;
    // std::cout << "voici bel" << bel2 << std::endl;
    // std::cout << "voici bel" << bel3 << std::endl;
    //2009-01-02,0
    //2022-03-29,47115.93
    if (atoi(bel1.c_str()) == 2009 && bel2 == "01" && atoi(bel3.c_str()) < 2)
    {
        std::cout << "there is no close data available" << std::endl;
        return ;
    }
    else if (atoi(bel1.c_str()) < 2009)
    {
        std::cout << "there is no close data available" << std::endl;
        return ;
    }
    else if ((atoi(bel1.c_str()) > 2022) && (atoi(bel1.c_str()) > 3 || atoi(bel1.c_str()) > 29))
    {
        //mettre la date en dur + le calcul
        // 47115.93 * le nb en question
        std::map<std::string, float>::iterator it;
        it = _ma.lower_bound(wait);
        it--;
        // std::cout << "voici id->second" << it->second << std::endl;
        int nb = it->second;
        int len = str.length() - 12;
        std::string cpy(str.substr(12, len));
        float nb2 = std::atof(cpy.c_str());
        float result = nb * nb2;
        if (result > float(2147483647))
            std::cout << "cannot print the result" << std::endl;
        else
            std::cout << "2022-03-29 => " << tmp[3] << " = " << result << std::endl;
    }
    else if (_ma.find(wait) != _ma.end())
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
        if (result > float(2147483647))
            std::cout << "cannot print the result" << std::endl;
        else
            std::cout << af << " => " << tmp[3] << " = " << result << std::endl;
    }
}
