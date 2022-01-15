#include "ruException.h"

#include <iostream>
ruException::ruException(const std::string& msg): msg(msg) {
}

ruException::~ruException() {
}

ruCubeStateException::ruCubeStateException(const std::string& msg): ruException(std::string("ruCubeStateException: ") + msg) {

}

ruCubeStateException::~ruCubeStateException() {
}

const char* ruCubeStateException::what() const noexcept {
    return msg.c_str();
}

ruCubeTurnException::ruCubeTurnException(uint8_t index): ruException(std::string("ruCubeTurnException: Cube turn index (which is ") + std::to_string(index) + ") out of range (which is [0:5])") {
}

ruCubeTurnException::~ruCubeTurnException() {

}

const char* ruCubeTurnException::what() const noexcept {
    return msg.c_str();
}



ruCubeFactoryException::ruCubeFactoryException(const std::string& msg): ruException(std::string("ruCubeFactoryException: ") + msg) {

}

ruCubeFactoryException::~ruCubeFactoryException() {

}

const char* ruCubeFactoryException::what() const noexcept {
    return msg.c_str();
}


ruCubeSolvedMaskException::ruCubeSolvedMaskException(const std::string& msg): ruException(std::string("ruCubeSolvedMaskException: ") + msg) {

}

ruCubeSolvedMaskException::~ruCubeSolvedMaskException() {
}

const char* ruCubeSolvedMaskException::what() const noexcept {
    return msg.c_str();
}



ruCubeScrambleException::ruCubeScrambleException(const std::string& msg): ruException(std::string("ruCubeScrambleException: ") + msg) {

}

ruCubeScrambleException::~ruCubeScrambleException() {
}

const char* ruCubeScrambleException::what() const noexcept {
    return msg.c_str();
}


ruCubeGeneratorParametersException::ruCubeGeneratorParametersException(const std::string &msg): ruException(std::string("ruCubeGeneratorParametersException: ") + msg) {

}

ruCubeGeneratorParametersException::~ruCubeGeneratorParametersException() {
}

const char* ruCubeGeneratorParametersException::what() const noexcept {
    return msg.c_str();
}


ruCubeMultiSolveHandlerException::ruCubeMultiSolveHandlerException(const std::string &msg): ruException(std::string("ruCubeMultiSolveHandlerException: ") + msg) {

}

ruCubeMultiSolveHandlerException::~ruCubeMultiSolveHandlerException() {
}

const char* ruCubeMultiSolveHandlerException::what() const noexcept {
    return msg.c_str();
}
