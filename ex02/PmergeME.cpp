#include "PmergeME.hpp"

Algo::Algo()
{

}

Algo::~Algo()
{

}

Algo &Algo::operator=(const Algo & copy)
{
    if (this != &copy)
        *this = copy;
    return *this;
}

Algo::Algo(const Algo & copy)
{
    *this = copy;
}

bool Algo::check_element_vector(char **argv, int argc, std::vector<double> vec)
{
    int i = 1;
    int j = 2;
    while (i < argc)
    {
        j = 1 + i;
        double nb = atof(argv[i]);
        while (argv[j])
        {
            if (nb == atof(argv[j]))
            {
                std::cout << "Error: two numbers are equal " << nb << " " << atof(argv[j]) << std::endl;
                return true;
            }
            else if (argv[j][0] == '-')
            {
                std::cout << "Error" << std::endl;
                return true;
            }
            else if (atof(argv[j]) > 2147483647)
            {
                std::cout << "Error: numbers are bigger than INT_MAX" << std::endl;
                return true;
            }
            j++;
        }
        i++;
        vec.push_back(nb);
    }
    return false;
}

void Algo::start_algo(size_t pair_ratio, std::vector<double> &vec)
{
    size_t actual_pair = pair_ratio - 1;
    while (actual_pair + pair_ratio < vec.size())
    {
        if (vec[actual_pair] > vec[actual_pair + pair_ratio])
        {
            for(size_t i = 0; i < pair_ratio; i++)
            {
                std::swap(vec[actual_pair - i], vec[actual_pair + pair_ratio - i]);
            }
        }
        actual_pair += pair_ratio * 2;
    }
    if (pair_ratio * 2 < vec.size())
        start_algo(pair_ratio * 2, vec);
    else
        return ;
    tri_dicoto(pair_ratio, actual_pair, vec);
}

void Algo::tri_dicoto(size_t pair_ratio, size_t actual_pair, std::vector<double> &vec)
{
    std::vector<double> vec_buf;
    std::vector<double>::iterator vec_it = vec.begin();
    std::vector<double>::iterator buf_it;
    size_t pl_check = 2;
    (void)actual_pair;

    size_t total;
    total = vec.size() / pair_ratio;
    size_t reach = 0;
    while (reach < total)
    {
        if (reach == pl_check)
        {
            for(size_t i = 0; i < pair_ratio; i++)
            {
                vec_buf.push_back(*vec_it);
                vec_it = vec.erase(vec_it);
            }
            reach++;
            pl_check += 2;
        }
        vec_it += pair_ratio;
        reach++;
    }
	if (vec_buf.size() < 1)
		return ;
    vec_it = vec.begin();
    std::vector<double>::iterator mid;
    std::vector<double>::iterator top = vec.end();
    std::vector<double>::iterator bot = vec.begin();
    int pair_size = vec_buf.size();
    buf_it = vec_buf.begin();
    int nb = 0;
    nb = vec_buf[pair_ratio - 1];
    while (pair_size > 0)
    {
        top = vec.end();
        while (is_pair_ratio(*top, pair_ratio, vec) == 0)
            top--;
        size_t i = 0;
        while (i < vec.size())
            i++;
        bot = vec.begin();
        while (42)
        {
            if (bot + pair_ratio > vec.end())
            {
                mid = top;
                break;
            }
            mid = find_middle(vec, top, pair_ratio, bot);
            if (std::distance(bot, top) <= (int)pair_ratio || top == bot)
                break;
            else if (*mid < nb)
                bot = mid;
            else if (*mid > nb)
            {
                if (mid - pair_ratio < vec.begin())
                    top = mid;
                else
                    top = mid - pair_ratio;
            }
        }
        vec_it = vec.begin();
        if (nb > *mid)
        {
            if (mid < top)
            {
                while (vec_it < mid)
                    vec_it++;
            }
            else
            {
                while (vec_it < top)
                    vec_it++;
            }
			if (nb > *top)
			{
				while (vec_it < top)
					vec_it++;
			}
            if (*vec_it > nb)
                insert_list(pair_ratio, buf_it, vec_buf, vec, vec_it, 0);
            else
                insert_list(pair_ratio, buf_it, vec_buf, vec, vec_it, 1);
        }
        else
        {
            if ((bot == vec.begin() && nb < *(bot + pair_ratio - 1)) || (bot + pair_ratio == mid && nb > *bot && pair_ratio > 1))
            {
				while (vec_it < bot)
					vec_it++;
            }
			else if (nb > *bot && nb < *mid)
			{
				while (vec_it < mid)
					vec_it++;
			}
            if (*vec_it > nb || (bot == vec.begin() && nb < *(bot + pair_ratio - 1)))
                insert_list(pair_ratio, buf_it, vec_buf, vec, vec_it, 0);
            else
                insert_list(pair_ratio, buf_it, vec_buf, vec, vec_it, 1);
        }
        pair_size -= pair_ratio;
        if (pair_size > 0)
        {
            buf_it += pair_ratio;
            nb = *(buf_it + pair_ratio - 1);
        }
    }
}

std::vector<double>::iterator Algo::find_middle(std::vector<double> vec, std::vector<double>::iterator top, int pair_ratio, std::vector<double>::iterator bot)
{
    std::vector<double>::iterator mid;
    std::vector<double>::iterator tmp = vec.begin();
    if (top == bot)
        return top;
    size_t dist = std::distance(bot, top);
    tmp = bot + (dist / 2);
    while (is_pair_ratio(*tmp, pair_ratio, vec) == 0 && tmp > vec.begin())
        tmp++;
    if (is_pair_ratio(*bot, pair_ratio, vec) == 0)
    {
        while (is_pair_ratio(*bot, pair_ratio, vec) == 0)
            bot++;
    }
    while (bot < tmp)
        bot += pair_ratio;
    mid = bot;
    return mid;
}

void Algo::insert_list(size_t pair_ratio, std::vector<double>::iterator buf_it, std::vector<double> vec_buf, std::vector<double> &vec, std::vector<double>::iterator vec_it, int plus)
{
    (void)vec_buf;
	for(size_t i = 0; i < pair_ratio; i++)
	{
		vec.insert(vec_it + plus + i, 1, *buf_it);
        buf_it++;
	}
}

bool Algo::is_pair_ratio(size_t nb_it, int pair_ratio, std::vector<double> vec)
{
    size_t i;
    if (pair_ratio > 1)
        i = pair_ratio - 1;
    else
        i = pair_ratio;
    while ((i + pair_ratio) < vec.size())
    {
        if (nb_it == vec[i])
            return 1;
        i += pair_ratio;
    }
    if (nb_it == vec[i])
        return 1;
    return 0;
}

void Algo::print_container(std::vector<double> vec)
{
    size_t i = 0;
    if (vec.size() < 1)
        return ;
    while (vec[i] != vec.back())
    {
        if (vec[i] == vec.back())
            break;
        std::cout << vec[i] << " ";
        i++;
    }
    std::cout << vec[i] << std::endl;
}

// template<typename T>
// void print_container(T vec)
// {
//     size_t i = 0;
//     std::cout << "voici print cointainer: ";
//     if (vec.size() < 1)
//     {
//         std::cout << "il n'y a rien dans ce vecteur" << std::endl;
//         return ;
//     }
//     while (vec[i] != vec.back())
//     {
//         if (vec[i] == vec.back())
//             break;
//         std::cout << vec[i] << " ";
//         i++;
//     }
//     std::cout << vec[i] << std::endl;
// }

// template<typename T>
// void print_container_pair_size(T vec, size_t pair_ratio)
// {
//     int i = 0;
//     while (vec[i] != vec.back())
//     {
//         std::cout << "[";
//         size_t j = 0;
//         while (j < pair_ratio && vec[i] != vec.back())
//         {
//             if (vec[i] == vec.back())
//                 break;
//             std::cout << " " << vec[i];
//             j++;
//             i++;
//         }
//         std::cout << " " << vec[i];
//         if (vec[i] == vec.back())
//             break;
//         i++;
//         std::cout << "] ";
//     }
//     std::cout << "] " << std::endl;
// }

bool Algo::check_element_vector_deque(char **argv, int argc, std::deque<double> vec2)
{
    int i = 1;
    int j = 2;
    while (i < argc)
    {
        j = 1 + i;
        double nb = atof(argv[i]);
        while (argv[j])
        {
            if (nb == atof(argv[j]))
            {
                std::cout << "Error: two numbers are equal " << nb << " " << atof(argv[j]) << std::endl;
                return true;
            }
            else if (argv[j][0] == '-')
            {
                std::cout << "Error" << std::endl;
                return true;
            }
            else if (atof(argv[j]) > 2147483647)
            {
                std::cout << "Error: numbers are bigger than INT_MAX" << std::endl;
                return true;
            }
            j++;
        }
        i++;
        vec2.push_back(nb);
    }
    return false;
}

void Algo::start_algo_deque(size_t pair_ratio, std::deque<double> &vec)
{
    size_t actual_pair = pair_ratio - 1;
    while (actual_pair + pair_ratio < vec.size())
    {
        if (vec[actual_pair] > vec[actual_pair + pair_ratio])
        {
            for(size_t i = 0; i < pair_ratio; i++)
            {
                std::swap(vec[actual_pair - i], vec[actual_pair + pair_ratio - i]);
            }
        }
        actual_pair += pair_ratio * 2;
    }
    if (pair_ratio * 2 < vec.size())
        start_algo_deque(pair_ratio * 2, vec);
    else
        return ;
    tri_dicoto_deque(pair_ratio, actual_pair, vec);
}

void Algo::tri_dicoto_deque(size_t pair_ratio, size_t actual_pair, std::deque<double> &vec)
{
    std::deque<double> vec_buf;
    std::deque<double>::iterator vec_it = vec.begin();
    std::deque<double>::iterator buf_it;
    size_t pl_check = 2;
    (void)actual_pair;

    size_t total;
    total = vec.size() / pair_ratio;
    size_t reach = 0;
    while (reach < total)
    {
        if (reach == pl_check)
        {
            for(size_t i = 0; i < pair_ratio; i++)
            {
                vec_buf.push_back(*vec_it);
                vec_it = vec.erase(vec_it);
            }
            reach++;
            pl_check += 2;
        }
        vec_it += pair_ratio;
        reach++;
    }
	if (vec_buf.size() < 1)
		return ;
    vec_it = vec.begin();
    std::deque<double>::iterator mid;
    std::deque<double>::iterator top = vec.end();
    std::deque<double>::iterator bot = vec.begin();
    int pair_size = vec_buf.size();
    buf_it = vec_buf.begin();
    int nb = 0;
    nb = vec_buf[pair_ratio - 1];
    while (pair_size > 0)
    {
        top = vec.end();
        while (is_pair_ratio_deque(*top, pair_ratio, vec) == 0)
            top--;
        size_t i = 0;
        while (i < vec.size())
            i++;
        bot = vec.begin();
        while (42)
        {
            // if (bot + pair_ratio > vec.end())
            if (static_cast<size_t>(std::distance(bot, vec.end())) < pair_ratio)
            {
                mid = top;
                break;
            }
            mid = find_middle_deque(vec, top, pair_ratio, bot);
            if (std::distance(bot, top) <= (int)pair_ratio || top == bot)
                break;
            else if (*mid < nb)
                bot = mid;
            else if (*mid > nb)
            {
                // if (mid - pair_ratio < vec.begin())
                if (static_cast<size_t>(std::distance(vec.begin(), mid)) < pair_ratio)
                    top = mid;
                else
                    top = mid - pair_ratio;
            }
        }
        vec_it = vec.begin();
        if (nb > *mid)
        {
            if (mid < top)
            {
                while (vec_it < mid)
                    vec_it++;
            }
            else
            {
                while (vec_it < top)
                    vec_it++;
            }
			if (nb > *top)
			{
				while (vec_it < top)
					vec_it++;
			}
            if (*vec_it > nb)
                insert_list_deque(pair_ratio, buf_it, vec_buf, vec, vec_it, 0);
            else
                insert_list_deque(pair_ratio, buf_it, vec_buf, vec, vec_it, 1);
        }
        else
        {
            if ((bot == vec.begin() && nb < *(bot + pair_ratio - 1)) || (bot + pair_ratio == mid && nb > *bot && pair_ratio > 1))
            {
				while (vec_it < bot)
					vec_it++;
            }
			else if (nb > *bot && nb < *mid)
			{
				while (vec_it < mid)
					vec_it++;
			}
            if (*vec_it > nb || (bot == vec.begin() && nb < *(bot + pair_ratio - 1)))
                insert_list_deque(pair_ratio, buf_it, vec_buf, vec, vec_it, 0);
            else
                insert_list_deque(pair_ratio, buf_it, vec_buf, vec, vec_it, 1);
        }
        pair_size -= pair_ratio;
        if (pair_size > 0)
        {
            buf_it += pair_ratio;
            nb = *(buf_it + pair_ratio - 1);
        }
    }
}

std::deque<double>::iterator Algo::find_middle_deque(std::deque<double> &vec, std::deque<double>::iterator top, int pair_ratio, std::deque<double>::iterator bot)
{
    std::deque<double>::iterator mid;
    std::deque<double>::iterator tmp = vec.begin();
    if (top == bot)
        return top;
    size_t dist = std::distance(bot, top);
    tmp = bot + (dist / 2);
    while (is_pair_ratio_deque(*tmp, pair_ratio, vec) == 0 && tmp > vec.begin())
        tmp++;
    if (is_pair_ratio_deque(*bot, pair_ratio, vec) == 0)
    {
        while (is_pair_ratio_deque(*bot, pair_ratio, vec) == 0)
            bot++;
    }
    while (bot < tmp)
        bot += pair_ratio;
    mid = bot;
    return mid;
}

void Algo::insert_list_deque(size_t pair_ratio, std::deque<double>::iterator buf_it, std::deque<double> &vec_buf, std::deque<double> &vec, std::deque<double>::iterator vec_it, int plus)
{
    (void)vec_buf;
	for(size_t i = 0; i < pair_ratio; i++)
	{
		std::deque<double>::iterator insert_pos = vec_it;
        std::advance(insert_pos, plus + i);
        vec.insert(insert_pos, *buf_it);
        buf_it++;
	}
}

bool Algo::is_pair_ratio_deque(size_t nb_it, int pair_ratio, std::deque<double> vec)
{
    size_t i;
    if (pair_ratio > 1)
        i = pair_ratio - 1;
    else
        i = pair_ratio;
    while ((i + pair_ratio) < vec.size())
    {
        if (nb_it == vec[i])
        {
            return 1;
        }
        i += pair_ratio;
    }
    if (nb_it == vec[i])
        return 1;
    return 0;
}

void Algo::print_container_deque(std::deque<double> vec)
{
    size_t i = 0;
    if (vec.size() < 1)
        return ;
    while (vec[i] != vec.back())
    {
        if (vec[i] == vec.back())
            break;
        std::cout << vec[i] << " ";
        i++;
    }
    std::cout << vec[i] << std::endl;
}
