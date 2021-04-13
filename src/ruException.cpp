#include "ruException.h"

#include <iostream>
ruException::ruException(std::string msg): msg(msg) {
}

ruException::~ruException() {
}

ruCubeStateException::ruCubeStateException(std::string msg): ruException(msg) {

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

