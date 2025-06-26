#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <unistd.h>

class Algo
{
    public:
    Algo();
    ~Algo();
    Algo&operator=(const Algo & copy);
    Algo(const Algo & copy);

    bool check_element_vector(char **argv, int argc, std::vector<double> vec);
    void start_algo(size_t pair, std::vector<double> &vec);
    void tri_dicoto(size_t pair_ratio, size_t actual_pair, std::vector<double> &vec, unsigned int nb);
    std::vector<double>::iterator find_middle(std::vector<double> vec, std::vector<double>::iterator top, int pair_ratio, std::vector<double>::iterator bot);
    bool is_pair_ratio(size_t nb_it, int pair_ratio, std::vector<double> vec);
	void Jacobstal(size_t pair_ratio, size_t actual_pair, std::vector<double> &vec);
    void insert_list(size_t pair_ratio, std::vector<double>::iterator buf_it, std::vector<double> vec_buf, std::vector<double> &vec, std::vector<double>::iterator vec_it, int plus);
    // void swap(double even);
    // void Algo<T>::Swap();

    private:
    // std::vector<double> _vec;
    std::deque<double> _deq;

}   ;

template<typename T>
void print_container(T vec);
template<typename T>
void print_container_pair_size(T vec, size_t pair_ratio);

//insertion binarie 
//insertion dycotomique
// 4 1 2 3
// 41 23 -> faire des paires
// 14 23 -> mettre l eplus grand a droite
// Recursion => 4 3 -> prendre les plus grands
// (2)3 (1)4 -> prendre les petits pour les deplacer a droite
// 1 2 3 4

#endif