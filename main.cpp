#include <iostream>
#include "game.h"
#include <string>
#include <vector>
#include <time.h>
#include <tuple>

using namespace std;

string press_touch(Game &game){
    string press;
    cout<<"Press une touche : ";
    cin>>press;
    if(press == "z"){
        game.top();
        return "z";
    }
    else if(press == "s"){
        game.down();
        return "s";
    }
    else if(press == "q"){
        game.left();
        return "q";
    }
    else if(press == "d"){
        game.right();
        return "d";
    }
    else if(press == "x"){
        return "x";
    }
    else{
        while(press != "q" || press != "d" || press != "s" || press != "z"){
            cout<<"Press q or d or s or z fdp : ";
            cin>>press;

            if(press == "z"){
                game.top();
                return "z";
            }
            else if(press == "s"){
                game.down();
                return "s";
            }
            else if(press == "q"){
                game.left();
                return "q";
            }
            else if(press == "d"){
                game.right();
                return "d";
            }
            else if(press == "x"){
                return "x";
            }
        }
    }
    return "x";
}


auto randomAI(Game &g){
    std::tuple<int, int> summary;
    vector <string> possibleMoves;
    bool win = false;
    bool lost = false;
    int highest = 0;
    int score = 0;
    bool victory = false;
    string enh = "";

    do{

        possibleMoves.clear();
        g.clearPossibleMoves();
        possibleMoves = g.getPossibleMoves();

        if(!possibleMoves.empty()){
            srand(time(NULL));
            int alea = rand() % possibleMoves.size();
            enh = g.press_touch_auto(possibleMoves[alea]);
        }
        lost = g.isLost(possibleMoves);
        win = g.checkWin();


    }while(win == false && lost == false);

    summary = std::make_tuple(g.getHighest(), g.getScore());
    return summary;
}


void play(){

    Game g;
    g.init();

    string enh = "";
    bool win = false;
    float score = 0;
    float highest = 0;
    int bestScore = 0;
    int nbWin = 0;

    auto summary = randomAI(g);
    highest = std::get<0>(summary);
    score = std::get<1>(summary);
    cout<< "1 : " << highest <<endl << "2 : " << score;


    /*for(int i = 0; i < 1000; i++){
        score = randomAI(g);
        if(bestScore < score)
            bestScore = score;
    }*/
    //g.print();

    /*do{
        enh = press_touch(g);
        g.print();
        win = g.checkWin();
        lost = g.isLost();


    }while(win == false || lost == false);*/

    /*if(lost)
        cout<<"Perdu !" <<endl + "Score : " + g.score <<endl;

    if(win)
        cout<<"GG t'as gagné !"<<endl + "Score : " + g.score <<endl +;*/
}


int main()
{

    play();


    return 0;
}
