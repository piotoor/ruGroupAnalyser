#ifndef RUCUBESINGLESOLVEHANDLERPOOL_H
#define RUCUBESINGLESOLVEHANDLERPOOL_H

#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <future>
#include <functional>
#include <stdexcept>
#include <fstream>
#include <string>

#include "ruCubeFileWriter.h"
#include "ruCubeSingleSolveHandler.h"
#include "ruLutCubeQueue.h"

class ruCubeSingleSolveHandlerThreadPool {
    public:
        ruCubeSingleSolveHandlerThreadPool( std::string fileName,
                                            std::shared_ptr<ruLutCubeQueue> cubeQueue,
                                            int bufferSize,
                                            size_t numOfCubesToFetch,
                                            size_t numOfThreads = 1,
                                            const solutionParameters &solParams = solutionParameters(),
                                            const solvedMasks &masks = solvedMasks(),
                                            const solveReportFlags &flags = solveReportFlags());

        virtual ~ruCubeSingleSolveHandlerThreadPool();
        ruCubeSingleSolveHandlerThreadPool(const ruCubeSingleSolveHandlerThreadPool&) = delete;
        ruCubeSingleSolveHandlerThreadPool& operator=(const ruCubeSingleSolveHandlerThreadPool&) = delete;

    private:

        std::vector<std::thread> threads;
        std::mutex stop_mutex;
        bool stop;

        std::shared_ptr<ruLutCubeQueue> cubeQueue;
        size_t numOfThreads;
        ruCubeFileWriter writer;
        int bufferSize;
        size_t numOfCubesToFetch;
};

#endif // RUCUBESINGLESOLVEHANDLERPOOL_H
