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
                                     int bufferSize,
                                     size_t numOfCubesToFetch,
                                     size_t numOfThreads = 1,
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
        std::shared_ptr<ruCubeFileWriter> writer;
        int bufferSize;
        size_t numOfCubesToFetch;
};

#endif // RUCUBESINGLESOLVEHANDLERPOOL_H
