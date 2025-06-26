#include "PmergeME.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "please put a least 2 elements" << std::endl;
        return 1;
    }
    Algo obj;
    std::cout << "liste de base: ";
    for(int i = 1; argv[i]; i++)
        std::cout << argv[i] << " ";
    std::cout << std::endl << std::endl;
    std::vector<double> vec;
    if (obj.check_element_vector(argv, argc, vec) == 1)
        return 1;
    for (int i = 1; i < argc; i++)
    {
        double nb = atof(argv[i]);
        // std::cout << "voici push " << nb << std::endl;
        vec.push_back(nb);
    }
    int pair = 1;
    obj.start_algo(pair, vec);
    size_t i = 1;
    while(i + 1 < vec.size())
    {
        if (i + 1== vec.size())
            break;
        if (vec[i] > vec[i + 1])
        {
            std::cout << "liste non trier" << std::endl;
            return 0;
        }
        i++;
    }
    std::cout << std::endl << "liste belle et bien trier" << std::endl;
    print_container(vec);
}

// liste probleme
//probleme /PmergeMe `shuf -i 1-25 -n 25 | tr "\n" " " -> finir commande oublier un detail
