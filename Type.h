#ifndef Type_H
#define Type_H
#include "LinkedList.h"
#include <iostream> 
#include "Redblack.h"
using namespace std;


class Type;
class Pokemon;
class Move;

class TypeNode{
    public:
        Type* defence = NULL;
        float multiplier = 0;    
};

class Type{
    public:
        string id = "";
        //LinkedList beacuses length of linkedlist will be less than 20
        LinkedList<TypeNode>* typeNodes = NULL;
        RBBST<Pokemon>* pokemonNodes = NULL;
        RBBST<Move>* moveNodes = NULL;
        Type(){
            typeNodes = new LinkedList<TypeNode>();
            pokemonNodes = new RBBST<Pokemon>();
            moveNodes = new RBBST<Move>();
        }
        void addNode(Type* type2,float mul){
            TypeNode* nn = new TypeNode();
            nn->defence = type2;
            nn->multiplier = mul;
            typeNodes->insertAtFront(nn);
        }     
        void addNode(Pokemon* pokemon){
            pokemonNodes->insertWithoutDuplication(pokemon);
        }
        void addNode(Move* move){
            moveNodes->insertWithoutDuplication(move);
        }
};


ostream& operator<<(ostream& stream, Type* type) {
  stream << type->id;
  return stream;
}
ostream& operator<<( ostream &output, const TypeNode* node)
{
    output << node->defence << " :: " << node->multiplier<<endl;
    return output;
};

#endif /* Type_H */