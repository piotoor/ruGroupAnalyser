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

#include "ruCubeFileWriter.h"
#include "ruCubeSingleSolveHandler.h"

class ruCubeSingleSolveHandlerPool {
    public:
        ruCubeSingleSolveHandlerPool(std::shared_ptr<ruCubeFileWriter> writer,
                                     size_t numOfThreads = 1,
                                     const solutionParameters &solParams = solutionParameters(),
                                     const solvedMasks &masks = solvedMasks(),
                                     const solveReportFlags &flags = solveReportFlags(),
                                     size_t bufferSize = 20 * 1024 * 1024);

        virtual ~ruCubeSingleSolveHandlerPool();

        void enqueueCube(ruLutCube cube);
    private:
        size_t numOfThreads;
        std::vector<std::thread> threads;

        std::queue<ruLutCube> cubes;

        std::mutex queue_mutex;
        std::condition_variable condition;
        bool stop;
        std::shared_ptr<ruCubeFileWriter> writer;
        size_t bufferSize;
};

#endif // RUCUBESINGLESOLVEHANDLERPOOL_H
