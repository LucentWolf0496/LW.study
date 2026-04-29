#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> stop{false};

struct MyThread {
    void operator()() {
        while (!stop)
            std::cout << "IN MYTHREAD\n";
    }
};

void my_thread(int) {
    while (!stop)
        std::cout << "in my_thread\n";
}

int main() {
    MyThread x;
    std::thread th(x);
    std::thread th1(my_thread, 100);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    stop = true;   // 通知线程停止

    th.join();
    th1.join();
}