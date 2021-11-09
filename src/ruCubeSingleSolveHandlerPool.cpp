#include "ruCubeSingleSolveHandlerPool.h"

ruCubeSingleSolveHandlerPool::ruCubeSingleSolveHandlerPool( std::shared_ptr<ruCubeFileWriter> writer,
                                                            int bufferSize,
                                                            size_t numOfCubesToFetch,
                                                            size_t numOfThreads,
                                                            const solutionParameters &solParams,
                                                            const solvedMasks &masks,
                                                            const solveReportFlags &flags): numOfThreads(numOfThreads),
                                                                                            stop(false),
                                                                                            bufferSize(bufferSize),
                                                                                            numOfCubesToFetch(numOfCubesToFetch) {

    for(size_t i = 0; i < numOfThreads; ++i) {
        threads.emplace_back([this, i, solParams, masks, flags, writer, bufferSize] {
                ruCubeSingleSolveHandler handler(solParams, masks, flags);
                std::cout << "yeah " + std::to_string(i) << std::endl;
                std::stringstream buff;
                std::queue<ruLutCube> cubes;
                //int k = 1;
                while (true) {
                    ruLutCube cube;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->cubes.empty(); });
                        if(this->stop && this->cubes.empty()) {
                            //if ( buff.tellg() > 0) {
                                writer->write(buff.str());

                            //}
                            return;
                        }
                        //int k = this->numOfCubesToFetch;
                        //while (k and !this->cubes.empty()) {
                            cube = std::move(this->cubes.front());
                            //cubes.emplace(std::move(this->cubes.front()));
                            this->cubes.pop();
                            //k--;
                        //}


                    }

                    //while (not cubes.empty()) {
                        //handler.solve(cubes.front());

                    handler.solve(cube);
                    handler.appendReport(buff);
                        //cubes.pop();


                    buff << "\n";
                    //if (buff.tellg() >= bufferSize) {
                    //if (k % 100 == 0) {
                        writer->write(buff.str());
                        buff.str( std::string() );
                        buff.clear();
                    //}
                    //++k;
                    //}
                }
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
