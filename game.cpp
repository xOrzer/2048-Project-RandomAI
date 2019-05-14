#include "game.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

/* ======== Fonctions ======== */

/* Aleatoire entre 2 et 4 */
int DeuxOuQuatre(){

    const int MAX = 100, MIN = 0;
    srand(time(NULL));
    int alea = (rand() % (MAX - MIN + 1)) + MIN;;

    // cout<<"Alea: "<< alea <<endl;

    if(alea < 90)
        return 2;
    else
        return 4;
}

/* ======== Methodes Game ======== */

/* Constructeur */
Game::Game(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            tab[i][j] = 0;
        }
    }
}

/* Affichage grille de jeu */
void Game::print(){
    //system("CLS");

    cout << " ============== 2048 ============== " << endl << endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << "    " << tab[i][j] << "    ";
        }
        cout << endl << endl;
    }
}

/* Initialisation grille de jeu */
void Game::init(){

    /* Init alea */
    srand(time(NULL));

    /* Tirage des aléatoires nombre (entre 2 et 4)*/
    int nbAlea = DeuxOuQuatre();
    int nbAlea2 = 0;
    if (nbAlea == 2)
        nbAlea2 = DeuxOuQuatre();
    else
        nbAlea2 = 2;

    /* Selection premier emplacement */
    int alea1 = rand()%4;
    int alea2 = rand()%4;
    /* Ajout dans le tableau */
    tab[alea1][alea2] = nbAlea;

    /* Selection deuxième emplacement */
    int alea3 = rand()%4;
    int alea4 = rand()%4;

    /* On s'assure que ce soit un emplacement différent du premier */
    while(alea3 == alea1 || alea4 == alea2){
        alea3 = rand()%4;
        alea4 = rand()%4;
    }

    /* Ajout dans le tableau */
    tab[alea3][alea4] = nbAlea2;



    /*tab[0][0] = 2;
    tab[0][1] = 2;
    tab[0][2] = 2;
    tab[0][3] = 4;*/


}


/* Methodes pratiques */



bool Game::checkWin(){

    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){
            if(tab[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;

}

void Game::clearPossibleMoves(){
    possibleMoves.clear();
}

vector<string> Game::getPossibleMoves(){
    if(possibleDown())
        possibleMoves.push_back("s");
    if(possibleTop())
        possibleMoves.push_back("z");
    if(possibleLeft())
        possibleMoves.push_back("q");
    if(possibleRight())
        possibleMoves.push_back("d");

    return possibleMoves;
}


bool Game::isLost(vector<string> v){
    if(v.empty()){
        return true;
    }

    return false;
}

void Game::alea(){

vector <int> nbCaseVide;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tab[i][j] == 0){
                nbCaseVide.push_back((4*i)+j);
            }
        }//end for j
    }//end for i

    int alea = rand()%nbCaseVide.size();
    int alea2 = DeuxOuQuatre();

    tab[0][nbCaseVide[alea]] = alea2;
}


/* Methode pour le haut */

bool Game::possibleTop(){

    bool isPossible = false;

    /* Décalage */
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){

            if(tab[i][j] != 0){
                if(tab[i][j] == tab[i-1][j] || tab[i-1][j] == 0){
                    isPossible = true;
                }
            }

        }//end for j
    }//end for i

    return isPossible;
}

void Game::decalageTop(){

    int k = 0;
    /* Décalage */
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){

            if(tab[i][j] != 0 && i == 0){
                k++;
            }

            if(tab[i][j] != 0 && i != 0){
                tab[k][j] = tab[i][j];
                if(i != k)
                    tab[i][j] = 0;
                k++;
            }
        //cout<<"tab["<<i<<"]["<<j<<"]: "<<tab[i][j]<<endl;
        }//end for j
        k=0;
    }//end for i
}

void Game::additionTop(){
    /* Addition */
    for(int j = 0; j < 4; j++){
            if(tab[0][j] == tab[1][j] && tab[0][j] == tab[2][j] && tab[0][j] == tab[3][j]){
                int nb = tab[0][j] + tab[0][j];
                tab[0][j] = nb;
                tab[1][j] = nb;
                tab[2][j] = 0;
                tab[3][j] = 0;
                score += 2*nb;
                continue;
            }
        for(int i = 0; i < 3; i++){
            if(tab[i][j] != 0){
                if(tab[i+1][j] == tab[i][j]){
                    tab[i][j] = (tab[i+1][j] + tab[i][j]);
                    tab[i+1][j] = 0;
                    score += tab[i][j];
                    break;
                }
            }
        }//end for j
    }//end for i
}

void Game::top(){

    bool test = false;
    test = possibleTop();

    if(test){
        decalageTop();
        additionTop();
        decalageTop();
        alea();
    }
    else{
        cout<<"Mouvement imposssible !"<<endl;
    }
}


/* Methode pour le bas */
bool Game::possibleDown(){

    bool isPossible = false;

    /* Décalage */
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){

            if(tab[i][j] != 0){
                if(tab[i][j] == tab[i+1][j] || tab[i+1][j] == 0){
                    isPossible = true;
                }
            }

        }//end for j
    }//end for i

    return isPossible;
}

void Game::decalageDown(){
    int k = 3;
    /* Décalage */
    for(int j = 3; j >= 0; j--){
        for(int i = 3; i >= 0; i--){

            if(tab[i][j] != 0 && i == 3){
                k--;
            }

            if(tab[i][j] != 0 && i != 3){
                tab[k][j] = tab[i][j];
                if(i != k)
                    tab[i][j] = 0;
                k--;
            }
        //cout<<"tab["<<i<<"]["<<j<<"]: "<<tab[i][j]<<endl;
        }//end for j
        k=3;
    }//end for i
}

void Game::additionDown(){
    /* Addition */
    for(int j = 3; j >= 0; j--){
            if(tab[0][j] == tab[1][j] && tab[0][j] == tab[2][j] && tab[0][j] == tab[3][j]){
                int nb = tab[0][j] + tab[0][j];
                tab[0][j] = 0;
                tab[1][j] = 0;
                tab[2][j] = nb;
                tab[3][j] = nb;
                score += 2*nb;
                continue;
            }
        for(int i = 3; i >= 0; i--){
            if(tab[i][j] != 0){
                if(tab[i-1][j] == tab[i][j]){
                    tab[i][j] = (tab[i-1][j] + tab[i][j]);
                    tab[i-1][j] = 0;
                    score += tab[i][j];
                    break;
                }
            }
        }//end for j
    }//end for i
}

void Game::down(){
    bool test = false;
    test = possibleDown();

    if(test){
        decalageDown();
        additionDown();
        decalageDown();
        alea();
    }
    else{
        cout<<"Mouvement imposssible !"<<endl;
    }
}


/* Methode pour la droite */

bool Game::possibleRight(){

    bool isPossible = false;

    /* Décalage */
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){

            if(tab[i][j] != 0  && j != 3){
                if(tab[i][j] == tab[i][j+1] || tab[i][j+1] == 0){
                    isPossible = true;
                }
            }

        }//end for j
    }//end for i

    return isPossible;
}

void Game::decalageRight(){
    int k = 3;
    /* Décalage */
    for(int i = 3; i >= 0; i--){
        for(int j = 3; j >= 0; j--){

            if(tab[i][j] != 0 && j == 3){
                k--;
            }

            if(tab[i][j] != 0 && j != 3){
                tab[i][k] = tab[i][j];
                if(j != k)
                    tab[i][j] = 0;
                k--;
            }
        //cout<<"tab["<<i<<"]["<<j<<"]: "<<tab[i][j]<<endl;
        }//end for j
        k=3;
    }//end for i
}

void Game::additionRight(){
    /* Addition */
    for(int i = 3; i >= 0; i--){
            if(tab[i][0] == tab[i][1] && tab[i][0] == tab[i][2] && tab[i][0] == tab[i][3]){
                int nb = tab[i][0] + tab[i][0];
                tab[i][0] = 0;
                tab[i][1] = 0;
                tab[i][2] = nb;
                tab[i][3] = nb;
                score += 2*nb;
                continue;
            }

        for(int j = 3; j >= 0; j--){
            if(tab[i][j] != 0){
                if(tab[i][j-1] == tab[i][j]){
                    tab[i][j] = (tab[i][j-1] + tab[i][j]);
                    tab[i][j-1] = 0;
                    score += tab[i][j];
                    break;
                }
            }
        }//end for j
    }//end for i
}

void Game::right(){
    bool test = false;
    test = possibleRight();

    if(test){
        decalageRight();
        additionRight();
        decalageRight();
        alea();
    }
    else{
        cout<<"Mouvement imposssible !"<<endl;
    }
}


/* Methode pour la gauche */

bool Game::possibleLeft(){

    bool isPossible = false;

    /* Décalage */
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){

            if(tab[i][j] != 0 && j != 0){
                if(tab[i][j] == tab[i][j-1] || tab[i][j-1] == 0){
                    isPossible = true;
                }
            }

        }//end for j
    }//end for i

    return isPossible;
}

void Game::decalageLeft(){
    int k = 0;
    /* Décalage */
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){

            if(tab[i][j] != 0 && j == 0){
                k++;
            }

            if(tab[i][j] != 0 && j != 0){
                tab[i][k] = tab[i][j];
                if(j != k)
                    tab[i][j] = 0;
                k++;
            }
        //cout<<"tab["<<i<<"]["<<j<<"]: "<<tab[i][j]<<endl;
        }//end for j
        k=0;
    }//end for i
}

void Game::additionLeft(){
    /* Addition */
    for(int i = 0; i < 4; i++){
            if(tab[i][0] == tab[i][1] && tab[i][0] == tab[i][2] && tab[i][0] == tab[i][3]){
                int nb = tab[i][0] + tab[i][0];
                tab[i][0] = nb;
                tab[i][1] = nb;
                tab[i][2] = 0;
                tab[i][3] = 0;
                score += 2*nb;
                continue;
            }
        for(int j = 0; j < 3; j++){
            if(tab[i][j] != 0){
                if(tab[i][j+1] == tab[i][j]){
                    tab[i][j] = (tab[i][j+1] + tab[i][j]);
                    tab[i][j+1] = 0;
                    score += tab[i][j];
                    break;
                }
            }
        }//end for j
    }//end for i
}

void Game::left(){
    bool test = false;
    test = possibleLeft();

    if(test){
        decalageLeft();
        additionLeft();
        decalageLeft();
        alea();
    }
    else{
        cout<<"Mouvement imposssible !"<<endl;
    }
}

string Game::press_touch_auto(string touch){

    if(touch == "z"){
        top();
        return "z";
    }
    else if(touch == "s"){
        down();
        return "s";
    }
    else if(touch == "q"){
        left();
        return "q";
    }
    else if(touch == "d"){
        right();
        return "d";
    }
}

int Game::getScore(){
    return score;
}

int Game::getHighest(){
    int highest = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tab[i][j] > highest){
                highest = tab[i][j];
            }
        }
    }
    return highest;
}



