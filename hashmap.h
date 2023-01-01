#ifndef Hashmap_H
#define Hashmap_H

#include<bits/stdc++.h>
#include <iostream>  
#include "Pokemon.h" 
using namespace std;

template <typename payload>
class Node{
    public:
        Node<payload>* next = NULL;
        payload* data;
};

template <typename type>
class Hashmap{
    public:
        Node<type>** map;
        int maxsize = 0;
        hash<string> hashfunc;
        Hashmap(int size){
            map = new Node<type>*[size]();
            maxsize = size;
        }
        //Hashfunction for table
        int hashfunction(string value){
            return hashfunc(value) % maxsize;
        }
        int hashfunction(int value){
            return hashfunc(value) % maxsize;
        }
        //Inserting into hashmap
        void insert(type* obj){
            int index = hashfunction(obj->id);
            if(search(obj->id)){
                delete obj;
                return;
            }
            Node<type>* nn = new Node<type>();
            nn->data = obj; 
            if(!map[index]){
                map[index] = nn;
            }
            else{
                Node<type>* loc = map[index];
                //Cycle to the last node
                while(loc->next){
                    loc = loc->next;
                }
                loc->next = nn; 
            }
            return;
        }
        //Searching for a type
        type* search(string id){
            transform(id.begin(), id.end(), id.begin(), ::toupper);
            int index = hashfunction(id);
            if(!map[index]){
                return NULL;
            }
            else if (map[index]->data->id == id){
                return map[index]->data;
            }
            else{
                Node<type>* loc = map[index];
                while(loc != NULL && loc->data->id != id){
                    loc = loc->next;
                }
                if(loc){
                    return loc->data;
                }
                return NULL;
            }
        }
};

#endif /* Hashmap_H */