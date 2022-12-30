#include <fstream>
#include <iostream>
#include "Pokemon.h" 
#include "Move.h"  
#include <vector>
#include <sstream>
#include "hashmap.h"
#include "Type.h"
#include "edges.h"
using namespace std;
class ParserClass{
    public:
        void parser(string FILENAME,Hashmap<Pokemon>* data,Hashmap<Type>* typeData){
            cout<<"                Pokemon                 "<<endl;
            cout<<"________________________________________"<<endl;
            fstream fin;
            fin.open(FILENAME, ios::in);
            string row;
            getline(fin,row);
            string word;
            vector<string> content;
            Pokemon* curr = NULL;
            Type* typeN = NULL;
            while(getline(fin,row)){
                content.clear();
                stringstream s(row);
                while(getline(s,word,',')){
                    content.push_back(word);
                }
                curr = new Pokemon();
                
                transform(content[1].begin(), content[1].end(), content[1].begin(), ::toupper);
                transform(content[2].begin(), content[2].end(), content[2].begin(), ::toupper);
                curr->id = content[1];
                typeN = typeData->search(content[2]);
                curr->typeOf = typeN; 
                curr->hp = stoi(content[3]);
                curr->attack = stoi(content[4]);
                curr->defense = stoi(content[5]);
                curr->spattack = stoi(content[6]);
                curr->spdef = stoi(content[7]);
                curr->speed = stoi(content[8]);

                typeN->addNode(curr);
                data->insert(curr);
            }    
            fin.close();
        }

        void parser(string FILENAME,Hashmap<Move>* data,Hashmap<Type>* typeData){
            cout<<"                MOVES                  "<<endl;
            cout<<"________________________________________"<<endl;
            fstream fin;
            fin.open(FILENAME, ios::in);
            string row;
            getline(fin,row);
            string word;
            vector<string> content;
            Move* curr = NULL;
            Type* typeN = NULL; 
            while(getline(fin,row)){
                content.clear();
                stringstream s(row);
                while(getline(s,word,',')){
                    content.push_back(word);
                }
                curr = new Move();
                
                transform(content[0].begin(), content[0].end(), content[0].begin(), ::toupper);
                transform(content[1].begin(), content[1].end(), content[1].begin(), ::toupper);
                transform(content[2].begin(), content[2].end(), content[2].begin(), ::toupper);
                transform(content[6].begin(), content[6].end(), content[6].begin(), ::toupper);
                transform(content[7].begin(), content[7].end(), content[7].begin(), ::toupper);

                curr->id = content[0];
                typeN = typeData->search(content[1]);
                curr->typeOf = typeN; 
                curr->category = content[2];
                
                if(content[3] != "?"){
                    curr->power = stoi(content[3]);
                }
                else{
                    curr->accuracy = 0;
                }
                
                if(content[4] != "?"){
                    curr->accuracy = stoi(content[4]);
                }
                else{
                    curr->accuracy = 100;
                }

                if(content[5] != "?"){
                    curr->pp = stoi(content[5]);
                }
                else{
                    curr->pp = 0;
                }

                if(content[6] != "none"){
                    curr->tm = content[6];
                }
                
                if(content[7] != "none"){
                    curr->effect = content[7];
                }

                if(content[8] != "?"){
                    curr->prob = stoi(content[8]);
                }
                else{
                    curr->prob = 100;
                }

                typeN->addNode(curr);
                data->insert(curr);
            }    
            fin.close();
        }


        void parser(string FILENAME,Hashmap<Type>* data){
            cout<<"                TYPES                 "<<endl;
            cout<<"________________________________________"<<endl;
            fstream fin;
            fin.open(FILENAME, ios::in);
            string row;
            getline(fin,row);
            string word;
            vector<string> content;
            Type* curr = NULL;
            Type* type2 = NULL;
            while(getline(fin,row)){
                content.clear();
                stringstream s(row);
                while(getline(s,word,',')){
                    content.push_back(word);
                }
                transform(content[0].begin(), content[0].end(), content[0].begin(), ::toupper);
                transform(content[1].begin(), content[1].end(), content[1].begin(), ::toupper);
                
                curr = data->search(content[0]);
                if(!curr){
                    curr = new Type();
                    curr->id = content[0];
                    data->insert(curr);
                }
                type2 = data->search(content[1]);
                if(type2 == NULL){
                    type2 = new Type();
                    type2->id = content[1];
                    data->insert(type2);
                }
                curr->addNode(type2,stof(content[3]));
                //curr->typeNodes->printlist();
            }    
            fin.close();
        }

        void parser(string FILENAME,Hashmap<Pokemon>* data){
            cout<<"                Evolution                 "<<endl;
            cout<<"________________________________________"<<endl;
            fstream fin;
            fin.open(FILENAME, ios::in);
            string row;
            getline(fin,row);
            string word;
            vector<string> content;
            Pokemon* curr = NULL;
            Pokemon* evo = NULL;
            while(getline(fin,row)){
                content.clear();
                stringstream s(row);
                while(getline(s,word,',')){
                    content.push_back(word);
                }

                transform(content[0].begin(), content[0].end(), content[0].begin(), ::toupper);
                transform(content[1].begin(), content[1].end(), content[1].begin(), ::toupper);

                
                curr = data->search(content[0]);
                evo = data->search(content[1]);
                if(!curr || !evo){
                    continue;
                }
                curr->evo = evo;
                evo->devo = curr;
                if(content[2] != ""){
                    curr->level = stoi(content[2]);
                }
                curr->condition = content[3];
                curr->type = content[4]; 
            }    
            fin.close();
        }
        void Wparser(string FILENAME,Hashmap<Pokemon>* pokemonData){
            cout<<"                Beats                 "<<endl;
            cout<<"________________________________________"<<endl;
            fstream fin;
            fin.open(FILENAME, ios::in);
            string row;
            string word;
            vector<string> content;
            while(getline(fin,row)){
                content.clear();
                stringstream s(row);
                while(getline(s,word,',')){
                    content.push_back(word);
                }

                transform(content[0].begin(), content[0].end(), content[0].begin(), ::toupper);
                transform(content[1].begin(), content[1].end(), content[1].begin(), ::toupper);                
                check(content[0],content[1],pokemonData); 
            }    
            fin.close();
        }

        

};