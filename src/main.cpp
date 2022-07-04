#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include "train.h"

std::mutex busyRailwayTrack;
std::mutex outputQueue;

void goTrain(Train* train)
{
    std::this_thread::sleep_for(std::chrono::seconds(train->getTime()));
    if (busyRailwayTrack.try_lock())
    {
        busyRailwayTrack.unlock();
    }
    else 
    {
        outputQueue.lock();
        std::cout << "    Train " << train->getName() << " is waiting for the release of the track" << std::endl;
        outputQueue.unlock();

    }
    
        
    busyRailwayTrack.lock();
    std::cout << " Train " << train->getName() << " has arrived at the railway station" << std::endl;
    
    std::cout << "Enter \"depart\" in order for train " << train->getName() << " to depart" << std::endl;
    std::string depart = "";
    while (depart != "depart")
    {
        std::cin >> depart;
    }
        
    std::cout << "The way is clear!Train " << train->getName() << " has left" << std::endl;
    busyRailwayTrack.unlock();
}

int main()
{
    constexpr int numberTrain = 3;
    std::vector<Train*> trains;
    for (int i = 0; i < numberTrain; ++i)
    {
        std::cout << "Train " << i + 1 << std::endl;
        std::cout << "Enter name train A,B or C: ";
        std::string name;
        std::cin >> name;
        std::cout << "Enter time on way (sec): ";
        int time;
        std::cin >> time;
        trains.push_back(new Train(name, time));
    }

    system("cls");

    std::vector <std::thread> trainThread;
    for (int i = 0; i < trains.size(); ++i)
    {
        trainThread.push_back(std::thread(goTrain, trains[i]));
    }
        
    for (auto& tr : trainThread)
    {
        if (tr.joinable()) tr.join();
    }    
}
