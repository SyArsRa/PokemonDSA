#include <iostream>
using namespace std;

#include "Pokemon.h" 
#include "hashmap.h"
#include "Move.h"
Pokemon* attackerData = NULL;
Pokemon* defenderData = NULL;
void check(string attacker,string defender,Hashmap<Pokemon>* pokemonData){
    if(attackerData == NULL || attackerData->id != attacker){
        attackerData = pokemonData->search(attacker);
    }
    defenderData = pokemonData->search(defender);
    attackerData->edges->insertWithoutDuplication(defenderData);
};

