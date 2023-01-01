#include "parser.h"
#include <iostream>


#include "Pokemon.h" 
#include "hashmap.h"
#include "Move.h"
#include "Type.h"
using namespace std;

void mainMenu(Hashmap<Type>* typeData,Hashmap<Pokemon>* pokemonData,Hashmap<Move>* moveData);

int main(){
    //ideal load factor of 0.75 where load factor = elements inserted into hashmap/buckets so 721/0.75 ~ 962 for pokemons
    
    ParserClass* p = new ParserClass();

    // Hashmap over bst for type beacuse it is being accessed again and again
    Hashmap<Type>* typeData = new Hashmap<Type>(24);
    Hashmap<Pokemon>* pokemonData = new Hashmap<Pokemon>(962);
    Hashmap<Move>* moveData = new Hashmap<Move>(811);
    //Parsers
    p->parser("data\\Types.csv",typeData);
    p->parser("data\\Pokemon.csv",pokemonData,typeData);
    p->parser("data\\Moves.csv",moveData,typeData);
    p->parser("data\\Evo.csv",pokemonData);
    p->Wparser("data\\Beats.csv",pokemonData);

    mainMenu(typeData,pokemonData,moveData);

    return 0;
}

//mainMenu of the programn
void mainMenu(Hashmap<Type>* typeData,Hashmap<Pokemon>* pokemonData,Hashmap<Move>* moveData){
    char choice = ' ';
    cout << "\e[1;35mInput '!' to terminate the program anytime.\e[0;37m" << endl;
    while (choice != '!') //while loop until '!' is entered
    {
        cout << "\n\x1b[36mPlease select an action: " << endl << endl;
        cout << "\t1. Read file data" << endl;
        cout << "\t2. Write to file" << endl;
        cout << "\t3. Print List" << endl;

        cout << "\x1b[0m"; cin >> choice; cout << endl;
        switch(choice)  //switch statement to check user input and calling respective functions
        {
        case('1'):
        {
            
        }; break;
        case('2'):
        {
            
        }; break;
        case('!'):
        {
            cout << "\e[1;33mProgram terminated." << endl;
        }; break;
        default:
            cout << "\x1b[31mInvalid action selected!\x1b[37m" << endl;
        }
    }
}
