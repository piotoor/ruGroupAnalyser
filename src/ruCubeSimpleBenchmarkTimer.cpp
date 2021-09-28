#include "ruCubeSimpleBenchmarkTimer.h"
#include <iostream>

ruCubeSimpleBenchmarkTimer::ruCubeSimpleBenchmarkTimer():start(std::chrono::steady_clock::now()), newline(true), printout(true) {

}

ruCubeSimpleBenchmarkTimer::ruCubeSimpleBenchmarkTimer(bool newline, bool printout):start(std::chrono::steady_clock::now()), newline(newline), printout(printout) {

}

ruCubeSimpleBenchmarkTimer::~ruCubeSimpleBenchmarkTimer() {
    if (printout) {
        const auto stop = std::chrono::steady_clock::now();
        std::cout << "(" << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms)";
        if (newline) {
            std::cout << std::endl;
        }
    }
}

std::string ruCubeSimpleBenchmarkTimer::getElapsedTimeStr() {
    const auto stop = std::chrono::steady_clock::now();
    return std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count());
}

std::chrono::milliseconds ruCubeSimpleBenchmarkTimer::getElapsedTime() {
    const auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}
