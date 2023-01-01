#ifndef Type_H
#define Type_H
#include <iostream> 
#include "BST.h"
#include "LinkedList.h"
using namespace std;


class Type;
class Pokemon;
class Move;

//class of each edge in linkedlist  with its details
class TypeEdge{
    public:
        string id = "";
        Type* defence = NULL;
        float multiplier = 0;    
};

//class for sotring type Type
class Type{
    public:
        string id = "";
        //LinkedList beacuses length of linkedlist will be less than 20
        //Linkedlist stores each edge
        LinkedList<TypeEdge>* typeEdges = NULL;
        BST<Pokemon>* pokemonNodes = NULL;
        BST<Move>* moveNodes = NULL;
        //constructor intializes each pointer
        Type(){
            typeEdges = new LinkedList<TypeEdge>();
            pokemonNodes = new BST<Pokemon>();
            moveNodes = new BST<Move>();
        }
        //function that adds new edges to linkedlist
        void addEdge(Type* type2,float mul){
            TypeEdge* nn = new TypeEdge();
            nn->id = type2->id;
            nn->defence = type2;
            nn->multiplier = mul;
            typeEdges->insertAtFront(nn);
        }     
        //function to add nodes to pokemonNodes BST
        void addNode(Pokemon* pokemon){
            pokemonNodes->insertWithoutDuplication(pokemon);
        }
        //function to add nodes to moveNodes BST
        void addNode(Move* move){
            moveNodes->insertWithoutDuplication(move);
        }
};


//overwritting cout operator for printing Type
ostream& operator<<(ostream& stream, Type* type) {
    //add red colour to type
    stream << "\033[1;31m" << type->id << "\033[0m";
    return stream;
}
//overwritting cout operator for printing TypeNode
ostream& operator<<( ostream &output, const TypeEdge* node)
{
    output << node->defence << " :: " << node->multiplier<<endl;
    return output;
};

#endif /* Type_H */