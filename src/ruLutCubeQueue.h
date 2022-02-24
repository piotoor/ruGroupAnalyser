#ifndef RULUTCUBEQUEUE_H
#define RULUTCUBEQUEUE_H

#include "ruCube.h"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

class ruLutCubeQueue {
    public:
        ruLutCubeQueue() = default;
        virtual ~ruLutCubeQueue() = default;
        void push(ruLutCube cube);
        std::optional<ruLutCube> pop();
        bool isEmpty();
        void stop();

    private:
        std::queue<ruLutCube> cubeQueue;
        std::mutex queue_mutex;
        std::condition_variable condition;

        bool stopped = false;
};

#endif // RULUTCUBEQUEUE_H
