#include <iostream>

#include "Pokemon.h"
#include "Move.h"
#include "Type.H"
#include "hashmap.h"

using namespace std;

//This function allows a player to select a move and calculates the damage done to the opponent. It takes in three parameters:
inline float turn(float hp, float multi, Move** moves)
{
    cout << "  Choose Your Move" << endl;
    for(int x = 0; x < 4; x++)
    {
        cout << x + 1 << ": " << moves[x] << endl;
    }

    int move = 0;
    cin >> move;
    move--;

    cout << "\e[1;35mDamage Done " << multi * (moves[move]->power) << endl;
    return hp - multi * (moves[move]->power);
}
//This is the main function that handles the Pokemon battle between two players. 
inline void Arena(Hashmap<Type>* typeData, Hashmap<Pokemon>* pokemonData, Hashmap<Move>* moveData)
{
    Pokemon* p1 = NULL;
    Pokemon* p2 = NULL;
    Move** moves1 = new Move*[4]();
    Move** moves2 = new Move*[4]();
    float hp1;
    float hp2;
    string name;


    while(!p1)
    {
        cout << "\e[1;34mPlayer 1 Select Your Pokemon" << endl;
        getline(cin, name);
        p1 = pokemonData->search(name);
    }
    cout << "Select From the following moves" << endl;
    p1->typeOf->moveNodes->inorder();
    for(int x = 0; x < 4; x++ )
    {
        while( moves1[x] == NULL )
        {
            cout << "Select Your " << x + 1 << "th Move" << endl;
            getline(cin,name);
            moves1[x] = moveData->search(name);
        }
    }

    while(!p2)
    {
        cout << "\e[1;31mPlayer 2 Select Your Pokemon" << endl;
        getline(cin,name);
        p2 = pokemonData->search(name);
    }
    cout << "Select From the following moves" << endl;
    p2->typeOf->moveNodes->inorder();

    for( int x = 0; x < 4; x++)
    {
        while(moves2[x] == NULL)
        {
            cout << "select your " << x + 1 << "th move" << endl;
            getline(cin,name);
            moves2[x] = moveData->search(name);
        }
    }
    hp1 = p1->defense + p1->defense + p1->spdef;
    hp2 = p2->defense + p2->defense + p2->spdef; 
    float multi1 = p1->typeOf->typeEdges->search(p2->typeOf->id)->multiplier;
    float multi2 = p1->typeOf->typeEdges->search(p2->typeOf->id)->multiplier;
    while(hp1 > 0 && hp2 > 0)
    {
        cout<<endl<<"\e[1;34mPlayer 1 HP "<<hp1<<endl;
        cout<<"\e[1;31mPlayer 2 HP "<<hp2<<endl<<endl;
        cout<<"\e[1;34mPlayer 1's turn"<<endl;
        hp2 = turn(hp2,multi1,moves1);
        if(hp2 <= 0)
        {
            cout << "\e[1;32mPlayer 1 wins";
            break;
        }

        cout <<"\e[1;31mPlayer 2's turn" << endl;
        hp1 = turn(hp1,multi2,moves2);
    }
    if(hp1 <= 0)
    {
        cout << "\e[1;32mPlayer 2 wins";
    }
}
