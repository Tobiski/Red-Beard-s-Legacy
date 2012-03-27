#ifndef TOPSCORE_H
#define TOPSCORE_H


class TopScore
{
    public:
        TopScore();
        virtual ~TopScore();

        int addNewScore(std::string nick, int shots, float accuracy, float score);

    protected:
    private:
};

#endif // TOPSCORE_H
