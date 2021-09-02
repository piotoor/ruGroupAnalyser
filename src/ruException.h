#ifndef RUEXCEPTION_H
#define RUEXCEPTION_H

#include <string>

class ruException {
    public:
        ruException(const std::string& msg);
        virtual ~ruException();
        virtual std::string what() const noexcept = 0;

    protected:
        std::string msg;

};

class ruCubeStateException: public ruException {
    public:
        ruCubeStateException(const std::string& msg = "Invalid cube state");
        virtual ~ruCubeStateException();
        std::string what() const noexcept override;
};

class ruCubeTurnException: public ruException {
    public:
        explicit ruCubeTurnException(uint8_t index);
        virtual ~ruCubeTurnException();
        std::string what() const noexcept override;
};

class ruCubeFactoryException: public ruException {
    public:
        ruCubeFactoryException(const std::string& msg = "Invalid cube type");
        virtual ~ruCubeFactoryException();
        std::string what() const noexcept override;
};

#endif // RUEXCEPTION_H

