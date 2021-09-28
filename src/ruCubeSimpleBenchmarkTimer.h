#ifndef RUCUBESIMPLEBENCHMARKTIMER_H
#define RUCUBESIMPLEBENCHMARKTIMER_H

#include <chrono>
#include <string>

class ruCubeSimpleBenchmarkTimer
{
    public:
        ruCubeSimpleBenchmarkTimer();
        explicit ruCubeSimpleBenchmarkTimer(bool newline, bool printout);
        virtual ~ruCubeSimpleBenchmarkTimer();
        std::string getElapsedTimeStr();
        std::chrono::milliseconds getElapsedTime();

    private:
        std::chrono::time_point<std::chrono::steady_clock> start;
        bool newline;
        bool printout;
};

#endif // RUCUBESIMPLEBENCHMARKTIMER_H
