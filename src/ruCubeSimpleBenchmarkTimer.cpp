#include "ruCubeSimpleBenchmarkTimer.h"
#include <iostream>

ruCubeSimpleBenchmarkTimer::ruCubeSimpleBenchmarkTimer():start(std::chrono::steady_clock::now()), newline(true) {

}

ruCubeSimpleBenchmarkTimer::ruCubeSimpleBenchmarkTimer(bool newline):start(std::chrono::steady_clock::now()), newline(newline) {

}

ruCubeSimpleBenchmarkTimer::~ruCubeSimpleBenchmarkTimer() {
    const auto stop = std::chrono::steady_clock::now();
    std::cout << "(" << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms)";
    if (newline) {
        std::cout << std::endl;
    }
}
