#include <iostream>
#include <thread>
#include <future>
#include <vector>

void getMin(std::vector<int> v, int i, std::promise<int> pr)
{
    size_t n = v.size();

    int minV{ i };
    for (int j = i + 1; j < n; j++)
    {
        if (v[j] < v[minV])
        {
            minV = j;
        }
    }
    pr.set_value(minV);
};
void print_vector(std::vector<int>& v)
{
    for (auto& v1 : v)
    {
        std::cout << v1 << " ";
    }
    std::cout << std::endl;
}
int main()
{
    std::vector<int> v{ 9,1,5,3,2,4 };
    std::cout << "Before: ";
    print_vector(v);

    auto n = v.size();

    for (int i = 0; i < n - 1; i++)
    {
        //1. promise
        std::promise<int> pr;
        //2. future
        std::future<int> fut = pr.get_future();
        //3. stream
        auto res = async(getMin, v, i, move(pr));
        //4. wait promise.set_value
        int minIndex = fut.get();

        //5. sort
        if (v[minIndex] != v[i])
        {
            std::swap(v[i], v[minIndex]);
        }

    }
    std::cout << "After: ";
    print_vector(v);

    return 0;
}
