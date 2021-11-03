#include "ruCubeSingleSolveHandlerPool.h"

ruCubeSingleSolveHandlerPool::ruCubeSingleSolveHandlerPool( size_t numOfThreads,
                                                            const solutionParameters &solParams,
                                                            const solvedMasks &masks,
                                                            const solveReportFlags &flags): numOfThreads(numOfThreads),
                                                                                            stop(false) {

    for(size_t i = 0; i < numOfThreads; ++i) {
        threads.emplace_back([this, i, solParams, masks, flags] {
                ruCubeSingleSolveHandler handler(solParams, masks, flags);
                std::cout << "yeah " + std::to_string(i) << std::endl;
                std::ofstream output(std::string("solutions_") + std::to_string(i) + std::string(".txt"));
                if (output.is_open()) {
                    std::cout << ":dupa" << std::endl;
                }
                while (true) {

                    ruLutCube cube;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->cubes.empty(); });
                        if(this->stop && this->cubes.empty())
                            return;
                        cube = std::move(this->cubes.front());
                        this->cubes.pop();
                    }

                    handler.solve(cube);
                    output << handler.getReport() << std::endl;

                }
                output.close();
            }
        );
    }
}

ruCubeSingleSolveHandlerPool::~ruCubeSingleSolveHandlerPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: threads)
        worker.join();
}

void ruCubeSingleSolveHandlerPool::enqueueCube(ruLutCube cube) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop) {
            throw std::runtime_error("Trying to enqueue cube on a stopped pool");
        }

        cubes.emplace(cube);
    }
    condition.notify_one();
}
