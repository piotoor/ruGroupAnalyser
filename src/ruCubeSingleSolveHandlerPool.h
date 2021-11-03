#ifndef RUCUBESINGLESOLVEHANDLERPOOL_H
#define RUCUBESINGLESOLVEHANDLERPOOL_H

#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <fstream>

#include "ruCubeSingleSolveHandler.h"

class ruCubeSingleSolveHandlerPool {
    public:
        ruCubeSingleSolveHandlerPool(size_t numOfThreads = 1,
                                     const solutionParameters &solParams = solutionParameters(),
                                     const solvedMasks &masks = solvedMasks(),
                                     const solveReportFlags &flags = solveReportFlags());

        virtual ~ruCubeSingleSolveHandlerPool();

        void enqueueCube(ruLutCube cube);
    private:
        size_t numOfThreads;
        std::vector<std::thread> threads;

        std::queue<ruLutCube> cubes;

        std::mutex queue_mutex;
        std::condition_variable condition;
        bool stop;
};

#endif // RUCUBESINGLESOLVEHANDLERPOOL_H
