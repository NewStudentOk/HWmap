#include <iostream>
#include <future>
#include <vector>
#include <algorithm>

void add(int& val)
{
    val++;
}

template<typename Iterator>
void parallel_for_each(Iterator first, Iterator last)
{
    auto length = std::distance(first, last);
    unsigned long const max_chunk_size = 2;

    if (length <= max_chunk_size)
    {
        std::for_each(first, last, add);
    }
    else
    {
        Iterator mid_point = first;
        std::advance(mid_point, length / 2);

        auto res = std::async(parallel_for_each<Iterator>, first, mid_point);
        parallel_for_each(mid_point, last);

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

    parallel_for_each(v.begin(), v.end());

    std::cout << "After: ";
    print_vector(v);

    return 0;
}