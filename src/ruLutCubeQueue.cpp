#include "ruLutCubeQueue.h"

void ruLutCubeQueue::push(ruLutCube cube) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    cubeQueue.push(cube);
    condition.notify_one();
}

std::optional<ruLutCube> ruLutCubeQueue::pop() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    this->condition.wait(   lock,
                            [this] {
                                return not this->cubeQueue.empty() or stopped;
                            });

    if (stopped) {
        if (not this->cubeQueue.empty()) {
            ruLutCube ans = std::move(cubeQueue.front());
            cubeQueue.pop();
            return ans;
        }
        return std::nullopt;
    } else {
        ruLutCube ans = std::move(cubeQueue.front());
        cubeQueue.pop();
        return ans;
    }
}

bool ruLutCubeQueue::isEmpty() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    return cubeQueue.empty();
}

void ruLutCubeQueue::stop() {
    stopped = true;
    this->condition.notify_all();
}
