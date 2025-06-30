#include "PmergeME.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "please put a least 2 elements" << std::endl;
        return 1;
    }
    Algo obj;
    std::vector<double> vec;
    if (obj.check_element_vector(argv, argc, vec) == 1)
        return 1;
    for (int i = 1; i < argc; i++)
    {
        double nb = atof(argv[i]);
        vec.push_back(nb);
    }
    int pair = 1;
    std::cout << "Before: ";
    obj.print_container(vec);

    clock_t start,end;
    start = clock();
    obj.start_algo(pair, vec);
    std::cout << "After: ";
    end = clock();
    obj.print_container(vec);
    double time_taken = double(end - start);
    std::cout << "Time to precess a range of " << vec.size() << " elements with vector : " << time_taken << "us" << std::endl;
    
    
    Algo obj2;
    std::deque<double> vec2;
    if (obj2.check_element_vector_deque(argv, argc, vec2) == 1)
        return 1;
    for (int i = 1; i < argc; i++)
    {
        double nb = atof(argv[i]);
        vec2.push_back(nb);
    }
    pair = 1;
    start = clock();
    obj2.start_algo_deque(pair, vec2);
    end = clock();
    time_taken = double(end - start);
    std::cout << "Time to precess a range of " << vec2.size() << " elements with deque : " << time_taken << "us" << std::endl;
    // size_t i = 1;
    // while(i + 1 < vec.size())
    // {
    //     if (i + 1== vec.size())
    //         break;
    //     if (vec[i] > vec[i + 1])
    //     {
    //         std::cout << "liste non trier" << std::endl;
    //         return 0;
    //     }
    //     i++;
    // }
    // std::cout << std::endl << "liste belle et bien trier" << std::endl;
}

// /./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
// Before: 141 79 526 321 [...]
// After: 79 141 321 526 [...]
// Time to process a range of 3000 elements with std::[..] : 62.14389 us
// Time to process a range of 3000 elements with std::[..] : 69.27212 us