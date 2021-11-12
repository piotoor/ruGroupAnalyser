#ifndef RULUTCUBEGENERATORTHREAD_H
#define RULUTCUBEGENERATORTHREAD_H

#include <thread>
#include "ruLutCubeQueue.h"
#include "ruLutCubeGenerator.h"

class ruLutCubeGeneratorThread {
    public:
        ruLutCubeGeneratorThread(const generatorParameters &genParams, std::shared_ptr<ruLutCubeQueue> cubeQueue);
        virtual ~ruLutCubeGeneratorThread();
        ruLutCubeGeneratorThread(const ruLutCubeGeneratorThread&) = delete;
        ruLutCubeGeneratorThread& operator=(const ruLutCubeGeneratorThread&) = delete;

    private:
        std::shared_ptr<ruLutCubeQueue> cubeQueue;
        std::unique_ptr<std::thread> worker;

};

#endif // RULUTCUBEGENERATORTHREAD_H
