#ifndef RUEXCEPTION_H
#define RUEXCEPTION_H

#include <exception>
#include <string>

class ruException : public std::exception
{
    public:
        ruException();
        virtual ~ruException();
        virtual std::string what() = 0;

    protected:
        std::string msg;

};

#endif // RUEXCEPTION_H
