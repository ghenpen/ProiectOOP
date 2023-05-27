#pragma once
#include <iostream>
class Error : public std::exception {
public:
    explicit Error(const char* message) : message(message) {}
    virtual const char* what() const throw() {
        return message.c_str();
    }
protected:
    std::string message;
};

class InputError : public Error {
public:
    explicit InputError(const char* message) : Error(message) {}
};

class DivisionByZero : public Error {
public:
    explicit DivisionByZero(const char* message) : Error(message) {}
};
class x : public Error {
public:
    explicit x(const char* message) : Error(message) {}
};
