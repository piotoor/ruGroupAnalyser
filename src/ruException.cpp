#include "ruException.h"

#include <iostream>
ruException::ruException(const std::string& msg): msg(msg) {
}

ruException::~ruException() {
}

ruCubeStateException::ruCubeStateException(const std::string& msg): ruException(msg) {

}

ruCubeStateException::~ruCubeStateException() {
}

std::string ruCubeStateException::what() const noexcept {
    return std::string("ruCubeStateException: " + msg);
}

ruCubeTurnException::ruCubeTurnException(uint8_t index): ruException(std::string("Cube turn index (which is ") + std::to_string(index) + ") out of range (which is [0:5])") {
}

ruCubeTurnException::~ruCubeTurnException() {

}

std::string ruCubeTurnException::what() const noexcept {
    return std::string("ruCubeTurnException: " + msg);
}



ruCubeFactoryException::ruCubeFactoryException(const std::string& msg): ruException(msg) {

}

ruCubeFactoryException::~ruCubeFactoryException() {

}

std::string ruCubeFactoryException::what() const noexcept {
    return std::string("ruCubeFactoryException: " + msg);
}


ruCubeSolvedMaskException::ruCubeSolvedMaskException(const std::string& msg): ruException(msg) {

}

ruCubeSolvedMaskException::~ruCubeSolvedMaskException() {
}

std::string ruCubeSolvedMaskException::what() const noexcept {
    return std::string("ruCubeSolvedMaskException: " + msg);
}



ruCubeScrambleException::ruCubeScrambleException(const std::string& msg): ruException(msg) {

}

ruCubeScrambleException::~ruCubeScrambleException() {
}

std::string ruCubeScrambleException::what() const noexcept {
    return std::string("ruCubeScrambleException: " + msg);
}
