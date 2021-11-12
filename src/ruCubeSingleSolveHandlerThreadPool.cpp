#include "ruCubeSingleSolveHandlerThreadPool.h"

ruCubeSingleSolveHandlerThreadPool::ruCubeSingleSolveHandlerThreadPool( std::string fileName,
                                                                        std::shared_ptr<ruLutCubeQueue> cubeQueue,
                                                                        int bufferSize,
                                                                        size_t numOfCubesToFetch,
                                                                        size_t numOfThreads,
                                                                        const solutionParameters &solParams,
                                                                        const solvedMasks &masks,
                                                                        const solveReportFlags &flags): numOfThreads(numOfThreads),
                                                                                                        stop(false),
                                                                                                        writer(fileName),
                                                                                                        bufferSize(bufferSize),
                                                                                                        numOfCubesToFetch(numOfCubesToFetch),
                                                                                                        cubeQueue(cubeQueue) {

    for(size_t i = 0; i < numOfThreads; ++i) {
        threads.emplace_back([this, i, solParams, masks, flags, numOfCubesToFetch] {
                ruCubeSingleSolveHandler handler(solParams, masks, flags);
                std::cout << "thread " + std::to_string(i) << std::endl;
                std::stringstream buff;
                int k = 0;
                while (true) {
                    ruLutCube cube;
                    {
                        if(this->stop && this->cubeQueue->isEmpty()) {
                            this->writer.write(buff.str());
                            return;
                        }
                        cube = this->cubeQueue->pop();
                    }

                    handler.solve(cube);
                    //handler.appendReport(buff);

                    buff << "\n";
//                    if (k == numOfCubesToFetch) {
//                        this->writer.write(buff.str());
//                        buff.str( std::string() );
//                        buff.clear();
//                        k = 0;
//                    }

                }
            }
        );
    }
}

ruCubeSingleSolveHandlerThreadPool::~ruCubeSingleSolveHandlerThreadPool() {
    {
        std::unique_lock<std::mutex> lock(stop_mutex);
        stop = true;
    }

    for(std::thread &worker: threads)
        worker.join();
}
