#include <iostream>
#include <future>
#include <vector>
#include <algorithm>

template<typename T>
void add(T& val)
{
    val++;
}

template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
    auto length = std::distance(first, last);
    unsigned long const max_chunk_size = 2;

    if (length <= max_chunk_size)
    {
        std::for_each(first, last, f);
    }
    else
    {
        Iterator mid_point = first;
        std::advance(mid_point, length / 2);

        auto res = std::async(parallel_for_each<Iterator, Func>, first, mid_point, f);
        parallel_for_each(mid_point, last, f);

        res.get();
    }
}

void print_vector(const std::vector<int>& v)
{
    for (auto v1 : v)
    {
        std::cout << v1 << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v {19, 11, 9, 6, 2, 1};
    std::cout << "Before: ";
    print_vector(v);

    parallel_for_each(v.begin(), v.end(), add<int>); // Передаем функцию в качестве аргумента

    std::cout << "After: ";
    print_vector(v);

    return 0;
}