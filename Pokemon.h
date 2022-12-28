#ifndef Pokemon_H
#define Pokemon_H

#include <iostream> 
#include "Type.H"
using namespace std;

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
        Pokemon* evo = NULL;
        Pokemon* devo = NULL;
        int level = 999;
        string condition = "";
        string type = "";
        Pokemon(){}
};
ostream& operator<<(ostream& stream, Pokemon* pokemon) {
  stream << pokemon->id;
  return stream;
}

#endif /* Pokemon_H */