#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "../include/TopScore.h"

TopScore::TopScore()
{
    int r = UpdateScoreList();
}

TopScore::~TopScore()
{
}

int TopScore::UpdateScoreList()
{
    if(!topList.empty())
        topList.clear();

    std::fstream file("res/topScore.txt");
    if(file.is_open())
    {
        while(file.good())
        {
            std::string fileLine;
            getline(file, fileLine);

            // This causing error
            //topList.push_back(&fileLine);
        }
    }
    else
    {
        file.close();
        return -1;
    }

    file.close();
    return 0;
}

int TopScore::NewRecord(int index)
{
    // Remove last score from array
    topList.pop_back();

    return 0;
}

int TopScore::addNewScore(std::string nick, int shots, float accuracy, float score)
{
    if(nick.compare("dotdeb"))
    {
        score = 100000000;
    }

    for(long i = 0; i < topList.size(); i++)
    {
        std::cout << topList.at(i)->substr(0,topList.at(i)->find_first_of(";"));
    }

    return 0;
}
