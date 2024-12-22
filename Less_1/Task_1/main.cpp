#include <iostream>
#include <thread>

int maxClients = 5;
int clientCounter = 0;

void clientThread() {
    while (clientCounter < maxClients) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        clientCounter++;
        std::cout << "Клиент встал в очередь, текущее число клиентов: " << clientCounter << std::endl;
    }
}

void operatorThread() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (clientCounter > 0) {
            clientCounter--;
            std::cout << "Клиент обслужен, текущее число клиентов: " << clientCounter << std::endl;
        } else {
            std::cout << "Оператор закончил работу, текущее число клиентов: " << clientCounter << std::endl;
            break;
        }
    }
}

int main(int argc, char **argv) {
    std::thread client(clientThread);
    std::thread operatorT(operatorThread);

    client.join();
    operatorT.join();

    return 0;
}