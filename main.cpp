#include <iostream>

#include "parser.h"
#include "Pokemon.h" 
#include "hashmap.h"
#include "Move.h"
#include "Type.h"
#include "Arena.h"
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
    while (choice != '!')
    {
        cout << "\n\x1b[36mPlease select an action: " << endl << endl;

        cout << "\t1. Find a Pokemon" << endl;
        cout << "\t2. Search for Type" << endl;
        cout << "\t3. Search for Move" << endl;
        cout << "\t4. Return Evolutionary Cycle" << endl;
        cout << "\t5. Return all Pokemon of an Element Type" << endl;
        cout << "\t6. Return all Moves of an Element Type" << endl;
        cout << "\t7. Check if one Pokemon dominates another" << endl;
        cout << "\t8. Return all Pokemon that one is dominant against" << endl;
        cout << "\t9. Return Pokemon of the same Element Type" << endl;
        cout << "\tA. Return the one with an upper-hand in a duel" << endl;
        cout << "\tB. Compare Stats of Two Pokemon" << endl;
        cout << "\tC. Return all potential Moves of a Pokemon" << endl;
        cout << "\tD. Compare Stats of Two Moves" << endl;
        cout << "\tE. Open Pokemon Arena" << endl;
        cout << "\t!. Terminate Program" << endl;
        

        cout << "\x1b[0m"; 
        string choiceStr;
        getline(cin,choiceStr);
        choice = choiceStr[0] ;
        cout<<endl;
        switch(choice)
        {
        case('1'):
        {
            string name;
            cout << "Enter the name of the Pokemon: ";
            getline(cin,name);
            Pokemon* p = pokemonData->search(name);
            if(p == NULL){
                cout << "\x1b[31mPokemon not found!\x1b[37m" << endl;
            }
            else{
                cout << "\x1b[32mPokemon found!\x1b[37m" << endl;
                cout << "Name: " << p->id << endl;
                cout << "Type of : " << p->typeOf << endl;
                cout << "HP: " << p->hp << endl;
                cout << "Attack: " << p->attack << endl;
                cout << "Defense: " << p->defense << endl;
                cout << "Special Attack: " << p->spattack << endl;
                cout << "Special Defense: " << p->spdef << endl;
                cout << "Speed: " << p->speed << endl;
            }
        };
        break;
        
        case('2'):
        {
            string name;
            cout << "Enter the name of the Type: ";
            getline(cin,name);
            Type* t = typeData->search(name);
            if(t == NULL)
            {
                cout << "\x1b[31mType not found!\x1b[37m" << endl; 
            }
            else
            {
                cout << "\x1b[32mType found!\x1b[37m" << endl;
                cout << "Name: " << t->id << endl << endl;
                cout << "\e[1;32mAGAINST :: EFFECTIVENESS MULTIPLIER\e[0;37m" << endl;
                t->typeEdges->printlist();
                
            }
        };
        break;

        case('3'):
        {
            string name;
            cout << "Enter the name of the Move: ";
            getline(cin,name);
            Move* m = moveData->search(name);
            if(m == NULL)
            {
                cout << "\x1b[31mMove not found!\x1b[37m" << endl; 
            }
            else
            {
                cout << "\x1b[32mMove found!\x1b[37m" << endl;
                cout << "Name: " << m->id << endl;
                cout << "Type of : " << m->typeOf << endl;
                cout << "Power: " << m->power << endl;
                cout << "Accuracy: " << m->accuracy << endl;
                cout << "PP: " << m->pp << endl;
                cout << "Effect: " << m->effect << endl;
            }
        };
        break;

        case('4'):
        {
            string name;
            cout << "Enter the name of the Pokemon to check for Evolutionary Cycle: ";
            getline(cin,name);
            Pokemon* p = pokemonData->search(name);
            if(p == NULL){
                cout << "\x1b[31mPokemon not found!\x1b[37m" << endl;
            }
            else
            {
                while(p->devo){
                    p = p->devo;
                }
                if(!p->evo){
                    cout << "\x1b[31mNo Evolutions\x1b[37m"<<endl;
                }
                while(p->evo){
                    cout<<"\033[1;30m------------------------------------------\033"<<endl;
                    cout << "\033[1;31mEvolves from: "<< "\033[0m" << p  << endl;
                    cout << "\033[1;31mEvolves to: " << "\033[0m" << p->evo << endl;
                    if (p->level == 999)
                    {
                        cout << "\033[1;31mLevel for Evolution is "<< "\033[0m" << "Not Level Dependent" << endl;
                    }
                    else
                    {
                        cout << "\033[1;31mLevel for Evolution is "<< "\033[0m" << p->level << endl;
                    }

                    if (p->condition == "")
                    {
                        cout << "\033[1;31mCondition for Evolution is : " << "\033[0m" << "No Condition" << endl;
                    }
                    else
                    {
                        cout << "\033[1;31mCondition for Evolution is : " << "\033[0m" << p->condition << endl;
                    }
                    cout << "\033[1;31mEvolution is achieved through: " << "\033[0m" << p->type << endl;
                    p = p->evo;
                }
            }
        };
        break;

        case('5'):
        {
            string name;
            cout << "Enter the name of the Type: ";
            getline(cin,name);
            Type* t = typeData->search(name);
            if(t == NULL)
            {
                cout << "\x1b[31mType not found!\x1b[37m" << endl; 
            }
            else
            {
                cout << "\x1b[32mType found!\x1b[37m" << endl;
                cout << "Name: " << t->id << endl << endl;
                cout << "\e[1;32mPOKEMON OF TYPE " << t->id << " ARE AS FOLLOWS" << "\e[0;37m" << endl;
                t->pokemonNodes->inorder();
            }
        };
        break;

        case('6'):
        {
            string name;
            cout << "Enter the name of the Type: ";
            getline(cin,name);
            Type* t = typeData->search(name);
            if(t == NULL)
            {
                cout << "\x1b[31mType not found!\x1b[37m" << endl; 
            }
            else
            {
                cout << "\x1b[32mType found!\x1b[37m" << endl;
                cout << "Name: " << t->id << endl << endl;
                cout << "\e[1;32mMOVES OF TYPE " << t->id << " ARE AS FOLLOWS" << "\e[0;37m" << endl;
                t->moveNodes->inorder();
            }
        };
        break;

        case('7'):
        {
            string name1,name2;

            cout << "Enter the name of the Pokemon that is the attacker: ";
            getline(cin,name1);

            cout << "Enter the name of the Pokemon that is defending: ";
            getline(cin,name2);
            
            Pokemon* p1 = pokemonData->search(name1);
            if(!p1){
                cout << "\x1b[31m"<<name1<<"not found!\x1b[37m" << endl;
                break;
            }

            Pokemon* p2 = pokemonData->search(name2);
            if(!p2){
                cout << "\x1b[31m"<<name2<<" not found!\x1b[37m" << endl; 
                break;
            }
            
            if(p1->edges->search(p2)){
                cout << "\e[1;32m" <<p1->id<< " wins against "<<p2->id<< "\e[0;37m" << endl;
            }
            else{
                cout << "\e[1;31m" <<p1->id<< " does not win against "<<p2->id<< "\e[0;37m" << endl;
            }

        };
        break;

        case('8'):
        {
            string name;

            cout << "Enter the name of the Pokemon that is the attacker: ";
            getline(cin,name);
            
            Pokemon* p = pokemonData->search(name);
            if(!p){
                cout << "\x1b[31m"<<name<<" not found!\x1b[37m" << endl;
                break;
            }

            
            cout << "\e[1;32mPOKEMON THAT " << p->id << " CAN DOMINATE ARE AS FOLLOWS" << "\e[0;37m" << endl;
            p->edges->inorder();
        };
        break;

        case('9'):
        {
            string name;
            cout << "Enter the name of the Pokemon: ";
            getline(cin,name);
            Pokemon* p = pokemonData->search(name);
            if(p == NULL)
            {
                cout << "\x1b[31mPokemon not found!\x1b[37m" << endl; 
            }
            else
            {
                cout << "\e[1;32mPOKEMON OF TYPE " << p->typeOf << " ARE AS FOLLOWS" << "\e[0;37m" << endl;
                p->typeOf->pokemonNodes->inorder();
            }
        };
        break;

        case('A'):
        {
            string name1, name2;
            cout << "Enter the name of the first Pokemon: ";
            getline(cin,name1);
            cout << "Enter the name of the second Pokemon: ";
            getline(cin,name2);
            Pokemon* p1 = pokemonData->search(name1);
            Pokemon* p2 = pokemonData->search(name2);
            if(p1 == NULL || p2 == NULL)
            {
                cout << "\x1b[31mPokemon not found!\x1b[37m" << endl; 
            }
            else
            {
                cout << "\x1b[32mPokemon found!\x1b[37m" << endl;
                cout << "Name: " << p1->id << endl;
                cout << "Name: " << p2->id << endl;
                if(p1->total > p2->total)
                {
                    cout << "\e[1;32m" << p1->id << " has higher stats than " << p2->id << "\e[0;37m" << endl;
                }
                else if(p1->total < p2->total)
                {
                    cout << "\e[1;32m" << p2->id << " has higher stats than " << p1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << p1->id << " and " << p2->id << " have equal stats and are evenly matched" << "\e[0;37m" << endl;
                }
            }
        };
        break;

        case('B'):
        {
            string name1, name2;
            cout << "Enter the name of the first Pokemon: ";
            getline(cin,name1);
            cout << "Enter the name of the second Pokemon: ";
            getline(cin,name2);
            Pokemon* p1 = pokemonData->search(name1);
            Pokemon* p2 = pokemonData->search(name2);
            if(p1 == NULL || p2 == NULL)
            {
                cout << "\x1b[31mPokemon not found!\x1b[37m" << endl; 
            }
            else
            {
                cout << "\x1b[32mPokemon found!\x1b[37m" << endl;
                cout << "Name: " << p1->id << endl;
                cout << "Name: " << p2->id << endl;
                if(p1->total > p2->total)
                {
                    cout << "\e[1;32m" << p1->id << " has higher total stats than " << p2->id << "\e[0;37m" << endl;
                }
                else if(p1->total < p2->total)
                {
                    cout << "\e[1;32m" << p2->id << " has higher total stats than " << p1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << p1->id << " and " << p2->id << " have equal total stats and are evenly matched" << "\e[0;37m" << endl;
                }

                //COMPARING HP

                if(p1->hp > p2->hp)
                {
                    cout << "\e[1;32m" << p1->id << " has higher hp than " << p2->id << "\e[0;37m" << endl;
                }
                else if(p1->hp < p2->hp)
                {
                    cout << "\e[1;32m" << p2->id << " has higher hp than " << p1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << p1->id << " and " << p2->id << " have hp" << "\e[0;37m" << endl;
                }

                //COMPARING ATTACK

                if(p1->attack > p2->attack)
                {
                    cout << "\e[1;32m" << p1->id << " has higher attack than " << p2->id << "\e[0;37m" << endl;
                }
                else if(p1->attack < p2->attack)
                {
                    cout << "\e[1;32m" << p2->id << " has higher attack than " << p1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << p1->id << " and " << p2->id << " have equal attack" << "\e[0;37m" << endl;
                }

                //COMPARING DEFENSE

                if(p1->defense > p2->defense)
                {
                    cout << "\e[1;32m" << p1->id << " has higher defense than " << p2->id << "\e[0;37m" << endl;
                }
                else if(p1->total < p2->total)
                {
                    cout << "\e[1;32m" << p2->id << " has higher defense than " << p1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << p1->id << " and " << p2->id << " have equal defense" << "\e[0;37m" << endl;
                }

                //COMPARING SPECIAL ATTACK

                if(p1->spattack > p2->spattack)
                {
                    cout << "\e[1;32m" << p1->id << " has Special Attack than " << p2->id << "\e[0;37m" << endl;
                }
                else if(p1->spattack < p2->spattack)
                {
                    cout << "\e[1;32m" << p2->id << " has higher Special Attack than " << p1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << p1->id << " and " << p2->id << " have equal Special Attack" << "\e[0;37m" << endl;
                }

                //COMPARING SPECIAL DEFENSE
                if(p1->spdef > p2->spattack)
                {
                    cout << "\e[1;32m" << p1->id << " has higher Special Defense than " << p2->id << "\e[0;37m" << endl;
                }
                else if(p1->spdef < p2->spdef)
                {
                    cout << "\e[1;32m" << p2->id << " has higher Special Defense than " << p1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << p1->id << " and " << p2->id << " have equal Special Defense" << "\e[0;37m" << endl;
                }
            }
        };
        break;

        case('C'):
        {
            string name;
            cout << "Enter the name of the Pokemon: ";
            getline(cin,name);
            Pokemon* p = pokemonData->search(name);
            Move* m = moveData->search(name);
            if(p == NULL)
            {
                cout << "\x1b[31mPokemon not found!\x1b[37m" << endl; 
            }
            else
            {
                p->typeOf->moveNodes->inorder();
            }
        };
        break;

        case('D'):
        {
            string name1, name2;
            cout << "Enter the name of the first move: ";
            getline(cin,name1);
            cout << "Enter the name of the second move: ";
            getline(cin,name2);
            Move* m1 = moveData->search(name1);
            Move* m2 = moveData->search(name2);
            if(m1 == NULL || m2 == NULL)
            {
                cout << "\x1b[31mMove not found!\x1b[37m" << endl;
            }
            else
            {
                cout << "Name: " << m1->id << endl;
                cout << "Name: " << m2->id << endl;
                if(m1->power > m2->power)
                {
                    cout << "\e[1;32m" << m1->id << " has higher power than " << m2->id << "\e[0;37m" << endl;
                }
                else if(m1->power < m2->power)
                {
                    cout << "\e[1;32m" << m2->id << " has higher power than " << m1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << m1->id << " and " << m2->id << " have equal power" << "\e[0;37m" << endl;
                }

                //COMPARING ACCURACY

                if(m1->accuracy > m2->accuracy)
                {
                    cout << "\e[1;32m" << m1->id << " has higher accuracy than " << m2->id << "\e[0;37m" << endl;
                }
                else if(m1->accuracy < m2->accuracy)
                {
                    cout << "\e[1;32m" << m2->id << " has higher accuracy than " << m1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << m1->id << " and " << m2->id << " have equal accuracy" << "\e[0;37m" << endl;
                }

                //COMPARING PP

                if(m1->pp > m2->pp)
                {
                    cout << "\e[1;32m" << m1->id << " has higher pp than " << m2->id << "\e[0;37m" << endl;
                }
                else if(m1->pp < m2->pp)
                {
                    cout << "\e[1;32m" << m2->id << " has higher pp than " << m1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << m1->id << " and " << m2->id << " have equal pp" << "\e[0;37m" << endl;
                }

                //COMPARING PROBABILITY

                if(m1->prob > m2->prob)
                {
                    cout << "\e[1;32m" << m1->id << " has higher probability than " << m2->id << "\e[0;37m" << endl;
                }
                else if(m1->prob < m2->prob)
                {
                    cout << "\e[1;32m" << m2->id << " has higher probability than " << m1->id << "\e[0;37m" << endl;
                }
                else
                {
                    cout << "\e[1;32m" << m1->id << " and " << m2->id << " have equal probability" << "\e[0;37m" << endl;
                }
            }
        };
        break;

        case('E'):
        {
            cout << "\e[1;33mOpening Arena"<< endl;
            Arena(typeData,pokemonData,moveData);
        };
        break;

        case('!'):
        {
            cout << "\e[1;33mProgram terminated." << endl;
        };
        break;
        
        default:
            cout << "\x1b[31mInvalid action selected!\x1b[37m" << endl;
        }
    }
}
