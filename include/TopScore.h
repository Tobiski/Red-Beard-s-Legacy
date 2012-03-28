#ifndef TOPSCORE_H
#define TOPSCORE_H

class TopScore
{
    public:
        TopScore();
        virtual ~TopScore();

        int addNewScore(std::string nick, int shots, float accuracy, float score);
        std::vector<std::string*> getScoreList() { return topList; }

    protected:
    private:
        int UpdateScoreList();  // allways clears topList and creates it's again
        int NewRecord(int index);
        std::vector<std::string*> topList;
};

#endif // TOPSCORE_H
