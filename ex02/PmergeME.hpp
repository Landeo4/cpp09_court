#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <ctime>
#include <cstddef>

class Algo
{
    public:
    Algo();
    ~Algo();
    Algo&operator=(const Algo & copy);
    Algo(const Algo & copy);

    bool check_element_vector(char **argv, int argc, std::vector<double> vec);
    void start_algo(size_t pair, std::vector<double> &vec);
    void tri_dicoto(size_t pair_ratio, size_t actual_pair, std::vector<double> &vec);
    std::vector<double>::iterator find_middle(std::vector<double> vec, std::vector<double>::iterator top, int pair_ratio, std::vector<double>::iterator bot);
    bool is_pair_ratio(size_t nb_it, int pair_ratio, std::vector<double> vec);
    void insert_list(size_t pair_ratio, std::vector<double>::iterator buf_it, std::vector<double> vec_buf, std::vector<double> &vec, std::vector<double>::iterator vec_it, int plus);

    void start_algo_deque(size_t pair, std::deque<double> &vec);
    void tri_dicoto_deque(size_t pair_ratio, size_t actual_pair, std::deque<double> &vec);
    std::deque<double>::iterator find_middle_deque(std::deque<double> &vec, std::deque<double>::iterator top, int pair_ratio, std::deque<double>::iterator bot);
    bool is_pair_ratio_deque(size_t nb_it, int pair_ratio, std::deque<double> vec);
    void insert_list_deque(size_t pair_ratio, std::deque<double>::iterator buf_it, std::deque<double> &vec_buf, std::deque<double> &vec, std::deque<double>::iterator vec_it, int plus);
    bool check_element_vector_deque(char **argv, int argc, std::deque<double> vec2);

    void print_container(std::vector<double> vec);
    void print_container_deque(std::deque<double> vec);
    private:
    std::deque<double> _deq;

}   ;

// template<typename T>
// template<typename T>
// void print_container_pair_size(T vec, size_t pair_ratio);

#endif