#ifndef RUEXCEPTION_H
#define RUEXCEPTION_H

#include <string>
#include <exception>

class ruException: public std::exception {
    public:
        ruException(const std::string& msg);
        virtual ~ruException();
        virtual const char* what() const noexcept = 0;

    protected:
        std::string msg;

};

class ruCubeStateException: public ruException {
    public:
        ruCubeStateException(const std::string& msg = "Invalid cube state");
        virtual ~ruCubeStateException();
        const char* what() const noexcept override;
};

class ruCubeTurnException: public ruException {
    public:
        explicit ruCubeTurnException(uint8_t index);
        virtual ~ruCubeTurnException();
        const char* what() const noexcept override;
};

class ruCubeFactoryException: public ruException {
    public:
        ruCubeFactoryException(const std::string& msg = "Invalid cube type");
        virtual ~ruCubeFactoryException();
        const char* what() const noexcept override;
};

class ruCubeSolvedMaskException: public ruException {
    public:
        ruCubeSolvedMaskException(const std::string& msg = "Invalid cube solved mask");
        virtual ~ruCubeSolvedMaskException();
        const char* what() const noexcept override;
};

class ruCubeScrambleException: public ruException {
    public:
        ruCubeScrambleException(const std::string& msg = "Invalid scramble");
        virtual ~ruCubeScrambleException();
        const char* what() const noexcept override;
};

class ruCubeGeneratorParametersException: public ruException {
    public:
        ruCubeGeneratorParametersException(const std::string& msg = "Invalid cube generator parameters");
        virtual ~ruCubeGeneratorParametersException();
        const char* what() const noexcept override;
};

class ruCubeMultiSolveHandlerException: public ruException {
    public:
        ruCubeMultiSolveHandlerException(const std::string &msg = "Not enough available disk space");
        virtual ~ruCubeMultiSolveHandlerException();
        const char* what() const noexcept override;
};
#endif // RUEXCEPTION_H
