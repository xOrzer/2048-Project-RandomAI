#include <iostream>
#include "game.h"
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>
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
    bool win = false;
    bool lost = false;
    int alea = 0;

    do{

        g.searchPossibleMoves();

        if(g.getPossibleMoves().size()!=0){
            if(g.getPossibleMoves().size()>1){
                alea = rand() % g.getPossibleMoves().size();
                g.press_touch_auto(g.getPossibleMoves()[alea]);
            }else{
                g.press_touch_auto(g.getPossibleMoves()[0]);
            }
        }

        if(g.getPossibleMoves().size()==0)
            lost = true;
        lost = g.isLost(g.getPossibleMoves());
        win = g.checkWin();

        g.clearPossibleMoves();

    }while(win == false && lost == false);

    return std::make_tuple(g.getHighest(), g.getScore());

}


/*auto play(Game &g){

    int bestScore = 0;
    int bestHighest = 0;

    std::tuple<int, int> summary (0,0);
    return randomAI(g);
    if(lost)
        cout<<"Perdu !" <<endl + "Score : " + g.score <<endl;

    if(win)
        cout<<"GG t'as gagné !"<<endl + "Score : " + g.score <<endl +;
}*/


int main()
{
    int bestScore = 0;
    int bestHighest = 0;
    std::tuple<int, int> summary (0,0);

    srand(time(NULL));

    for(int i = 0; i<10000; i++){

        Game g;
        g.init();

        summary = randomAI(g);

        if(std::get<0>(summary) > bestHighest)
            bestHighest = std::get<0>(summary);
        if(std::get<1>(summary) > bestScore)
            bestScore = std::get<1>(summary);

    }

    cout<< "Plus grande valeur atteinte : " << bestHighest <<endl << "Meilleur score : " << bestScore<<endl;


    return 0;
}
