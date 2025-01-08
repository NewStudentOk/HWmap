#include <iostream>
#include <thread>
#include <vector>
#include <iomanip>
#include <chrono>

void sumVectors(const std::vector<int> &vector1, const std::vector<int> &vector2, std::vector<int> &resultVector,
                size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        resultVector[i] = vector1[i] + vector2[i];
    }
}

int main() {
    std::cout << "Количество аппаратных ядер: " << std::thread::hardware_concurrency() << "\n\n";
    std::cout << std::setw(12) << "\t\t   1000" << "\t\t    10000" << "\t       100000" << "\t     1000000" << "\n";

    std::vector<int> numOfThreads{1, 2, 4, 8, 16};
    std::vector<int> sizeOfVector{1000, 10000, 100000, 1000000};

    for (auto &countThread : numOfThreads) {
        std::cout << std::endl << countThread
                  << (countThread == 1 ? " поток" : (countThread < 5 ? " потока" : " потоков"));

        for (auto &countVector : sizeOfVector) {
            std::vector<int> vector1(countVector, 1); // Инициализация значениями 1
            std::vector<int> vector2(countVector, 2); // Инициализация значениями 2
            std::vector<int> resultVector(countVector); // Вектор для хранения результатов

            std::vector<std::thread> threads;
            size_t partOfTheSize = countVector / countThread;
            auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < countThread; ++i) {
                size_t startIdx = i * partOfTheSize;
                size_t endIdx = (i == countThread - 1) ? countVector : (i + 1) * partOfTheSize;

                threads.push_back(std::thread(sumVectors, std::ref(vector1), std::ref(vector2),
                                              std::ref(resultVector), startIdx, endIdx));
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