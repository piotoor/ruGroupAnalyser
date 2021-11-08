#include "ruCubeSingleSolveHandlerPool.h"

ruCubeSingleSolveHandlerPool::ruCubeSingleSolveHandlerPool( std::shared_ptr<ruCubeFileWriter> writer,
                                                            size_t numOfThreads,
                                                            const solutionParameters &solParams,
                                                            const solvedMasks &masks,
                                                            const solveReportFlags &flags,
                                                            int bufferSize ): numOfThreads(numOfThreads),
                                                                                 stop(false),
                                                                                 bufferSize(bufferSize) {

    for(size_t i = 0; i < numOfThreads; ++i) {
        threads.emplace_back([this, i, solParams, masks, flags, writer, bufferSize] {
                ruCubeSingleSolveHandler handler(solParams, masks, flags);
                std::cout << "yeah " + std::to_string(i) << std::endl;
                std::stringstream buff;

                while (true) {

                    ruLutCube cube;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->cubes.empty(); });
                        if(this->stop && this->cubes.empty()) {
                            if ( buff.tellg() > 0) {
                                writer->write(buff.str());

                            }
                            return;
                        }
                        cube = std::move(this->cubes.front());
                        this->cubes.pop();
                    }

                    handler.solve(cube);
                    // write to a buffer, and when full write and empty
                   //buff += handler.getReport() + "\n";
                   handler.appendReport(buff);
                   buff << "\n";
                    if (buff.tellg() >= bufferSize) {
                        writer->write(buff.str());
                        buff.str( std::string() );
                        buff.clear();
                    }


                }
                //output.close();
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
