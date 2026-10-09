#pragma once


struct Argument{
    float x;
};


struct FilterArgs{
    std::string name;
    std::vector<Argument> args;
};
