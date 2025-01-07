#include <iostream>
#include <thread>
#include <vector>
#include <iomanip>
#include <chrono>
#include <mutex>

void sumVectors(double &sumOfVectors, const std::vector<int> &newVector1, const std::vector<int> &newVector2,
                std::mutex &mtx) {
    double localSum = 0;
    for (size_t i = 0; i < newVector1.size(); ++i) {
        localSum += newVector1.at(i) + newVector2.at(i);
    }
    std::lock_guard<std::mutex> lock(mtx);
    sumOfVectors += localSum;
}

int main() {
    std::cout << "Количество аппаратных ядер: " << std::thread::hardware_concurrency() << "\n\n";
    std::cout << std::setw(12) << "\t\t   1000" << "\t\t    10000" << "\t       100000" << "\t     1000000" << "\n";

    std::vector<int> vector1;
    std::vector<int> vector2;
    std::vector<int> numOfThreads{1, 2, 4, 8, 16};
    std::vector<int> sizeOfVector{1000, 10000, 100000, 1000000};

    for (auto &countThread : numOfThreads) {
        std::cout << std::endl << countThread
                  << (countThread == 1 ? " поток" : (countThread < 5 ? " потока" : " потоков"));

        for (auto &countVector : sizeOfVector) {
            vector1.resize(countVector, 1);
            vector2.resize(countVector, 2);
            std::vector<std::thread> threads;
            double sumOfVectors = 0;
            std::mutex mtx;

            int partOfTheSize = static_cast<int>(countVector / countThread);
            auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < countThread; i++) {
                std::vector<int> newVector1(vector1.begin() + i * partOfTheSize, vector1.begin() +
                                                                                 (i == countThread - 1 ? countVector : (i + 1) * partOfTheSize));
                std::vector<int> newVector2(vector2.begin() + i * partOfTheSize, vector2.begin() +
                                                                                 (i == countThread - 1 ? countVector : (i + 1) * partOfTheSize));

                threads.push_back(
                        std::thread(sumVectors, std::ref(sumOfVectors), newVector1, newVector2, std::ref(mtx)));
            }

            for (auto &it : threads) {
                it.join();
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> totalTime = end - start;
            std::cout << std::setw(16) << totalTime.count() << "ms";
        }
        std::cout << "\n\n";
    }
    return 0;
}