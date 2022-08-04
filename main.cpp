#include <iostream>
#include <thread>
#include <mutex>

float times[6];
std::string names[6];
std::mutex times_access;
std::mutex names_access;

void swimmer(const float speed, const int number) {
    float distance = 0;
    float time = 0;
    while (distance < 100.0) {
        for (int i = 0; i < 100; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            distance += speed * 0.01;
            time +=0.01;
            if (distance >= 100.0) {
                break;
            }
        }
        if (distance > 100.0) {
            distance = 100.0;
        }
        names_access.lock();
        std::cout << "Swimmer " << names[number] << " swims " << distance << "meters." << std::endl;
        names_access.unlock();

    }
    times_access.lock();
    times[number] = time;
    times_access.unlock();
}

void sort() {
    for (int i = 0; i < 5; i++) {
        for (int j = i +1; j < 6; j++)
            if (times[i] > times[j]) {
                std::swap(times[i], times[j]);
                std::swap(names[i], names[j]);
            }
    }
}

int main() {
    float speed[6];

    for (int i = 0; i < 6; i++) {
        std::cout << "Enter name for swimmer #" << i << ": ";
        std::getline(std::cin, names[i]);
        std::cout << "Enter speed for swimmer #" << i << ": ";
        std::cin >> speed[i];
        std::cin.clear();
        std::cin.ignore();
    }
    std::thread swimmer0(swimmer, speed[0], 0);
    std::thread swimmer1(swimmer, speed[1], 1);
    std::thread swimmer2(swimmer, speed[2], 2);
    std::thread swimmer3(swimmer, speed[3], 3);
    std::thread swimmer4(swimmer, speed[4], 4);
    std::thread swimmer5(swimmer, speed[5], 5);
    swimmer0.join();
    swimmer1.join();
    swimmer2.join();
    swimmer3.join();
    swimmer4.join();
    swimmer5.join();
    sort();
    for (int i = 0; i < 6; i++) {
        std::cout << "Swimmer " << names[i] << " has time: " << times[i] <<std::endl;
    }
    return 0;
}
