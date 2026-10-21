#pragma once

#include <exception>


class FileNotFoundException : std::exception {
    
};

class BadFileFormat : std::exception {

};

class BadCommandLineArgument : std::exception {

};

class FilterDoesNotExist : std::exception {

};

class BadFilterArgument : std::exception {

};

