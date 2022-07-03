#pragma once

#include <iostream>
#include <string>

class Train
{
public:
    Train(std::string name, int time) : name(name), timeOnWay(time) {}
    
    std::string getName()
    {
        return name;
    }

    int getTime()
    {
        return timeOnWay;
    }
private:

    std::string name = "unknown";
    int timeOnWay = 0;
};
