#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../include/TopScore.h"

TopScore::TopScore()
{
    //ctor
}

TopScore::~TopScore()
{
    //dtor
}

int TopScore::addNewScore(std::string nick, int shots, float accuracy, float score)
{
    if(nick.compare("dotdeb"))
    {
        score = 100000000;
    }

    std::string fileContent;

    /* Open handles for reading and writing to file */
    std::ifstream rfile("../res/topcore.txt");
    if(rfile.is_open())
    {
        while(rfile.good())
        {
            getline(rfile, fileContent);
            std::istringstream token(fileContent);
            std::string scoreString;

            getline(token, scoreString, ';');
            std::istringstream scoreStream(scoreString);
            float fileScore;
            scoreStream >> fileScore;
        }
        rfile.close();
    }
    else
    {
        rfile.close();
        return -1;
    }


    return 0;
}
