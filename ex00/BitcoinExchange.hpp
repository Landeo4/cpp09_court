#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <string.h>

class BitcoinExchange
{
    public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange &operator=(const BitcoinExchange & copy);
    BitcoinExchange(const BitcoinExchange & copy);

    // BitcoinExchange(char **argv);
    bool check_file(char **argv);
    bool verify_line(std::string line);
    bool fill_container();
    void execute_line(char *buf, double *tmp, std::string str);


    private:
    // std::ifstream _file;
    std::map<std::string, float>    _ma;

}   ;

#endif