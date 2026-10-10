#pragma once

#include <exception>


class FileNotFoundException : std::exception {

};

class BadCommandLineArgument : std::exception {

};

