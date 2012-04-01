#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "../include/TopScore.h"

TopScore::TopScore()
{
    fileName = "res/topScore.txt";
    int r = UpdateScoreList();
}

TopScore::~TopScore()
{
}

void TopScore::setScoreList()
{
    std::ofstream file;
    file.open(fileName, std::ios::trunc);
    if(file.is_open())
    {
        for(int i = 0; i < topList.size(); i++)
        {
             file << topList[i] << "\n";
        }
    }
    file.close();
}

int TopScore::UpdateScoreList()
{
    if(!topList.empty())
        topList.clear();

    std::ifstream file;
    file.open(fileName);
    if(file.is_open())
    {
        while(file.good())
        {
            std::string fileLine;
            getline(file,fileLine);

            topList.push_back(fileLine);
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

int TopScore::addNewScore(std::string nick, int shots, float accuracy, float score)
{
    int j = 0;
    for(long i = 0; i < topList.size(); i++, j++)
    {
        /* translate string to float */
        std::string sOldScore = topList.at(i).substr(0,topList.at(i).find_first_of(";"));
        float oldScore;
        std::istringstream i(sOldScore);
        i >> oldScore;


        if(score > oldScore)
        {
            // Remove last score from array
            topList.pop_back();

            for(int i=0; i < topList.size(); i++)
                std::cout << topList[i] << std::endl;

            // Convert float back to string
            std::stringstream s;
            s << score;
            std::stringstream accur;
            accur << accuracy;
            std::stringstream shot;
            shot << shots;

            //Create new string to be added
            std::string record;
            record = s.str() + ";" + nick + ";" + accur.str() + ";" + shot.str();

            topList.insert(topList.begin()+j, record);
            setScoreList();
            break;
        }
    }

    return 0;
}

std::vector<std::string> TopScore::getScoreList()
{
    return topList;
}


