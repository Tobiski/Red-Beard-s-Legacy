#ifndef TOPSCORE_H
#define TOPSCORE_H

class TopScore
{
    public:
        TopScore();
        virtual ~TopScore();

        int addNewScore(std::string nick, int shots, float accuracy, int score);
        std::vector<std::string> getScoreList();

    protected:
    private:
        void setScoreList();
        int UpdateScoreList();  // allways clears topList and creates it's again
        std::vector<std::string> topList;

        char* fileName;
};

#endif // TOPSCORE_H
