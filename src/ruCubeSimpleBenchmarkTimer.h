#ifndef RUCUBESIMPLEBENCHMARKTIMER_H
#define RUCUBESIMPLEBENCHMARKTIMER_H

#include <chrono>

class ruCubeSimpleBenchmarkTimer
{
    public:
        ruCubeSimpleBenchmarkTimer();
        explicit ruCubeSimpleBenchmarkTimer(bool newline);
        virtual ~ruCubeSimpleBenchmarkTimer();

    private:
        std::chrono::time_point<std::chrono::steady_clock> start;
        bool newline;
};

#endif // RUCUBESIMPLEBENCHMARKTIMER_H
