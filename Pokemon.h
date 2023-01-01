#ifndef Pokemon_H
#define Pokemon_H

#include <iostream> 
#include "Type.H"
#include "BST.h"
using namespace std;

//Pokemon class that is created for each pokemon
class Pokemon{
    public:
        string id = "";
        Type* typeOf = NULL;
        int hp = 0;
        int attack = 0;
        int defense = 0;
        int spattack = 0;
        int spdef = 0;
        int speed = 0;
        int total = 0;
        //stores evolution
        Pokemon* evo = NULL;
        //stores last form
        Pokemon* devo = NULL;
        int level = 999;
        string condition = "";
        string type = "";
        //Stores edges 
        BST<Pokemon>* edges = new BST<Pokemon>;
        Pokemon(){}
};
//overwritting cout operator for printing Pokemon
ostream& operator<<(ostream& stream, Pokemon* pokemon) {
  stream << pokemon->id;
  return stream;
}

#endif /* Pokemon_H */  