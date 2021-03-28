#ifndef RUEXCEPTION_H
#define RUEXCEPTION_H

#include <exception>
#include <string>

class ruException : public std::exception {
    public:
        ruException(std::string msg);
        virtual ~ruException();
        virtual std::string what() = 0;

    protected:
        std::string msg;

};

class ruCubeStateException: public ruException {
    public:
        ruCubeStateException(std::string msg = "Invalid cube state");
        virtual ~ruCubeStateException();
        std::string what();
};

class ruCubeTurnException: public ruException {
    public:
        ruCubeTurnException(std::string msg = "Cube turn index out of range");
        virtual ~ruCubeTurnException();
        std::string what();
};

#endif // RUEXCEPTION_H
