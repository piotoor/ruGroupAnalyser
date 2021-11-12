#include "ruLutCubeGeneratorThread.h"

ruLutCubeGeneratorThread::ruLutCubeGeneratorThread(const generatorParameters &genParams,
                                                   std::shared_ptr<ruLutCubeQueue> cubeQueue): cubeQueue(cubeQueue) {
    worker = std::make_unique<std::thread>([this, genParams] () {
        ruLutCubeGenerator generator;
        generator.init(genParams);

        while (generator.hasNext()) {
            this->cubeQueue->push(generator.next());
        }

        std::cout << "finished generating" << std::endl;
        return;
    });
}

ruLutCubeGeneratorThread::~ruLutCubeGeneratorThread() {
    worker->join();
}
