#ifndef Move_H
#define Move_H

#include <iostream>

#include "Type.h" 

using namespace std;

class Move
{
public:
    string id = "";
    Type* typeOf = NULL;
    string category = "";
    int power = 0;
    int accuracy = 0;
    int pp = 0;
    string tm = "";
    string effect = "";
    int prob = 100;
    Move(){}
};
//cout overwrite to print move object
inline ostream & operator << (ostream& stream, Move* move)
{
    stream << move->id;
    return stream;
}

#endif /* Move_H */