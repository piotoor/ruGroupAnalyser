#ifndef RULUTCUBEQUEUE_H
#define RULUTCUBEQUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

#include "ruCube.h"

class ruLutCubeQueue {
    public:
        ruLutCubeQueue();
        virtual ~ruLutCubeQueue();
        void push(ruLutCube cube);
        std::optional<ruLutCube> pop();
        bool isEmpty();
        void stop();

    private:
        std::queue<ruLutCube> cubeQueue;
        std::mutex queue_mutex;
        std::condition_variable condition;

        bool stopped;
};

#endif // RULUTCUBEQUEUE_H
