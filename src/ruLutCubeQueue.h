#ifndef RULUTCUBEQUEUE_H
#define RULUTCUBEQUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>

#include "ruCube.h"

class ruLutCubeQueue {
    public:
        ruLutCubeQueue();
        virtual ~ruLutCubeQueue();
        void push(ruLutCube cube);
        ruLutCube pop();
        bool isEmpty();


    private:
        std::queue<ruLutCube> cubeQueue;
        std::mutex queue_mutex;
        std::condition_variable condition;
};

#endif // RULUTCUBEQUEUE_H
