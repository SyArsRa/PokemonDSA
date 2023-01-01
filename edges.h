#include <iostream>

#include "Pokemon.h" 
#include "hashmap.h"
#include "Move.h"

using namespace std;

Pokemon* attackerData = NULL;
Pokemon* defenderData = NULL;

//Function that fetches the attackerData and defenderData from hashmap and adds and edge in attackerData to defenderData 
inline void check(string attacker,string defender,Hashmap<Pokemon>* pokemonData)
{
    if(attackerData == NULL || attackerData->id != attacker)
    {
        attackerData = pokemonData->search(attacker);
    }
    
    defenderData = pokemonData->search(defender);
    attackerData->edges->insertWithoutDuplication(defenderData);
};

