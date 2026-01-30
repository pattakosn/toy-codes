#include <atomic>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <thread>
#include "gui.h"

std::atomic<bool> running{true};

int main(int argc, char** argv)
{
    std::thread worker_gui(gui);

    //running.store(false); 
    while (running.load())
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    worker_gui.join();

    return EXIT_SUCCESS;
}
