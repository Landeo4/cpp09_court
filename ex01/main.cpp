#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc > 3)
    {
        std::cout << "too many arguments" << std::endl;
        return 1;
    }
    else if (argc < 2)
    {
        std::cout << "please put 2 arguments" << std::endl;
        return 1;
    }
    RPN obj;
    if (obj.check_args(argv) == 1)
        return 1;
}
