#include <iostream>
using namespace std;

template <typename datatype>
class ListNode{
	public:
		datatype* data;
		ListNode* next = NULL; 
};

template <typename datatype>
class LinkedList{
	public:
		ListNode<datatype>* start;
		ListNode<datatype>* end;
		ListNode<datatype>* loc;
		ListNode<datatype>* preloc;
		LinkedList(){
			start = NULL;
			end = NULL;
			loc = NULL;
			preloc = NULL;
		}
		bool isEmpty(){
			if (start == NULL){
				return true;
			}
			else{
				return false;
			}
		}
		void insertAtFront(datatype* value){
			ListNode<datatype>* temp = new ListNode<datatype>();
			temp->data = value;
			temp->next = start;
			if (start == NULL){
				end = temp;
			}
			start = temp;
		}
		void insertAtBack(datatype* value){
			ListNode<datatype>* temp = new ListNode<datatype>();
			temp->data = value;
			if (start == NULL){
				start = temp;
			}
			else{
				end->next = temp;
			}
			end = temp;
		}
		void printlist(){
			loc = start;
			while(loc != NULL){
				cout<<loc->data<<" ";
				loc = loc->next;
			}
			cout<<endl;
		}
		void search(datatype* value){
			loc = start;
			preloc = NULL;
			while(loc != NULL && loc->data < value){
				preloc = loc;
				loc = loc->next;
			}
			if(loc != NULL && value != loc->data){
				loc = NULL;
			} 
			
		}
		void insertSorted(datatype* value){
			search(value);
			if(loc != NULL){
				cout<<"Value Alredy Exists In List"<<endl;
			}
			else if (preloc == NULL){
				insertAtFront(value);
			}else if (preloc == end){
				insertAtBack(value);
			}else{
				ListNode<datatype>* temp = new ListNode<datatype>();
				temp->data = value;
				temp->next = preloc->next;
				preloc->next = temp;
			}
		}
		void Delete(datatype* value){
			search(value);
			if (loc != NULL){
				if (preloc == NULL){
					start = loc->next;
				}else{
					preloc->next = loc->next;
				}
				if(loc == end){
					end = preloc;	
				}	
				delete loc;
			}
			else{
				cout<<"Value Doesnt exist in the list"<<endl;
			}
		}
		void DestroyList(){
			while(start != NULL){
				loc = start;
				start = start->next;
				delete loc;
			}
			cout<<"List Destroyed"<<endl;
		}
};
