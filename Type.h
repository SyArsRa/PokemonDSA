#ifndef Type_H
#define Type_H
#include <iostream> 
#include "BST.h"
#include "LinkedList.h"
using namespace std;


class Type;
class Pokemon;
class Move;

class TypeNode{
    public:
        string id = "";
        Type* defence = NULL;
        float multiplier = 0;    
};

class Type{
    public:
        string id = "";
        //LinkedList beacuses length of linkedlist will be less than 20
        LinkedList<TypeNode>* typeNodes = NULL;
        BST<Pokemon>* pokemonNodes = NULL;
        BST<Move>* moveNodes = NULL;
        Type(){
            typeNodes = new LinkedList<TypeNode>();
            pokemonNodes = new BST<Pokemon>();
            moveNodes = new BST<Move>();
        }
        void addNode(Type* type2,float mul){
            TypeNode* nn = new TypeNode();
            nn->id = type2->id;
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