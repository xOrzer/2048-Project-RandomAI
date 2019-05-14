#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>

class Game
{
    public:
        Game();
        void print();
        void init();
        void top();
        void down();
        void left();
        void right();
        std::string press_touch_auto(std::string touch);
        std::vector<std::string> getPossibleMoves();
        void clearPossibleMoves();
        bool checkWin();
        bool isLost(std::vector<std::string> v);
        int getScore();
        int getHighest();




    protected:


    private:
        int tab[4][4];
        std::vector<std::string> possibleMoves;
        int score = 0;
        int nbPlayed = 0;

        bool possibleTop();
        void decalageTop();
        void additionTop();

        bool possibleDown();
        void decalageDown();
        void additionDown();

        bool possibleRight();
        void decalageRight();
        void additionRight();

        bool possibleLeft();
        void decalageLeft();
        void additionLeft();


        void alea();
};

#endif // GAME_H
