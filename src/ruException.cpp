#include "ruException.h"

ruException::ruException(std::string msg): msg(msg) {
    //ctor
}

ruException::~ruException() {
    //dtor
}



ruCubeStateException::ruCubeStateException(std::string msg): ruException(msg) {

}

ruCubeStateException::~ruCubeStateException() {
}

std::string ruCubeStateException::what() {
    return "ruCubeStateException: " + msg;
}



ruCubeTurnException::ruCubeTurnException(std::string msg): ruException(msg) {

}

ruCubeTurnException::~ruCubeTurnException() {

}

std::string ruCubeTurnException::what() {
    return "ruCubeTurnException: " + msg;
}

