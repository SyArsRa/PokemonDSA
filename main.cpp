#include "parser.h"
#include <iostream>


#include "Pokemon.h" 
#include "hashmap.h"
#include "Move.h"
#include "Type.h"
using namespace std;

int main(){
    //ideal load factor of 0.75 where load factor = elements inserted into hashmap/buckets so 721/0.75 ~ 962 for pokemons
    
    ParserClass* p = new ParserClass();

    // Hashmap over bst for type beacuse it is being accessed again and again
    Hashmap<Type>* typeData = new Hashmap<Type>(24);
    Hashmap<Pokemon>* pokemonData = new Hashmap<Pokemon>(962);
    Hashmap<Move>* moveData = new Hashmap<Move>(811);
    
    p->parser("data\\Types.csv",typeData);
    p->parser("data\\Pokemon.csv",pokemonData,typeData);
    p->parser("data\\Moves.csv",moveData,typeData);
    p->parser("data\\Evo.csv",pokemonData);

    pokemonData->search("Blastoise")->typeOf->typeNodes->printlist();
    pokemonData->search("Charmander")->typeOf->moveNodes->inorder();

    return 0;
}
