#pragma once

#include <exception>
#include <string>
#include <stdexcept>


class FileNotFoundException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class BadFileFormatException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class EmptyKernelException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class UnableToWriteFileException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class BadCommandLineArgumentException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class FilterDoesNotExistException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class BadFilterArgumentException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

