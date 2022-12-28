#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;

template <typename ct>
class BSTNode{
  public:
	ct* data;
    int balance = 0;
	BSTNode* leftChild = NULL;
	BSTNode* rightChild = NULL;
};

template <typename ct>
class BST{
  public:
	BSTNode<ct>* root = NULL;
	BSTNode<ct>* loc = NULL;
	BSTNode<ct>* ploc = NULL;
	bool isEmpty(){
		return root == NULL;
	}
	void search(ct* val){
		loc = root;
		ploc = NULL;
		while(loc != NULL && loc->data->id != val->id){
			ploc = loc;
			if(loc->data->id > val->id ){
				loc = loc->leftChild;
			}
			else{
				loc = loc->rightChild;
			}
		}
	}
	void insertWithoutDuplication(ct* val){
		search(val);
		if(loc != NULL){
			cout<<"Value already in the BST"<<endl;
			return;
		}
		BSTNode<ct>* nn = new BSTNode<ct>();
        nn->data = val;
        if(ploc == NULL){
        root = nn;
        return;
        }
        
        if(ploc->data->id >= val->id){
            ploc->leftChild = nn;
        }
        else{
            ploc->rightChild = nn;
        }
    } 	
    void inorder(){
        if(root == NULL){
        return;
        }
        inorder(root->leftChild);
        cout<<root->data<<endl;
        inorder(root->rightChild);
    }
    void inorder(BSTNode<ct>* curr){
        if(curr == NULL){
        return;
        }
        inorder(curr->leftChild);
        cout<<curr->data<<endl;
        inorder(curr->rightChild);
    } 
    ct biggestval(){
        BSTNode<ct>* temp = root;
        while(temp->rightChild != NULL){
        temp = temp->rightChild;
        }
        return temp->data;
    }
    ct smallestval(){
        BSTNode<ct>* temp = root;
        while(temp->leftChild != NULL){
        temp = temp->leftChild;
        }
        return temp->data;
    }
    void printLeaf(BSTNode<ct>* curr){
        if(curr == NULL){
        return;
        }
        if(curr->leftChild == NULL && curr->rightChild == NULL){
        cout<<curr->data<<endl;
        return;
        }
        printLeaf(curr->leftChild);
        printLeaf(curr->rightChild);
        return;
    }
    int countLeaf(int count,BSTNode<ct>* curr){
        if(curr == NULL){
        return 0;
        }
        if(curr->leftChild == NULL && curr->rightChild == NULL){
        count++;
        }
        else{
        count += countLeaf(root->leftChild);
        count += countLeaf(root->rightChild);
        }
        return count;
    }
    int countInternal(int count,BSTNode<ct>* curr){
        if(curr == NULL){
        return 0;
        }
        if(curr->leftChild == NULL && curr->rightChild == NULL){
        return 0;
        }
        else{
        count++;
        count += countInternal(root->leftChild);
        count += countInternal(root->rightChild);
        }
        return count;
    }
    int depthOfTree(BSTNode<ct>* curr){
        if(curr == NULL){
        return -1;
        }
        return 1 + max(depthOfTree(curr->rightChild),depthOfTree(curr->leftChild)); 
    }
    int heightOfTree(BSTNode<ct>* curr,int cHeight){
        if(curr == NULL){
        return cHeight;
        }
        return max(heightOfTree(curr->rightChild,cHeight+1),heightOfTree(curr->leftChild,cHeight+1));
    }
    void deleteNode(ct val){
        search(val);
        if(!loc){
            cout<<"Value Not Found"<<endl;
            return;
        }
        BSTNode<ct>* replace = loc->rightChild;
        if(loc->leftChild && loc->rightChild){
            BSTNode<ct>* prereplace = loc;
            while(replace->leftChild){
                prereplace = replace;
                replace = replace->leftChild;
            }
            prereplace->leftChild = replace->rightChild;
            replace->leftChild = loc->leftChild;
            replace->rightChild = loc->rightChild;
        }
        else if (loc->leftChild){
            replace = loc->leftChild;
        }
        else if (loc->rightChild){
            replace = loc->rightChild;
        }
        else{
            replace = NULL;
        }
        
        if(!ploc){
                root = replace;
            } 
            else if(ploc->leftChild == loc) {
                ploc->leftChild = replace;
            }
            else{
                ploc->rightChild = replace;
            }
        delete loc;
    }
    void destroyNode(BSTNode<ct>* curr){
        if(curr == NULL){
            return;
        }
        destroyNode(curr->leftChild);
        destroyNode(curr->leftChild);
        delete curr; 
        return;
    }
    void destroy(){
        destroyNode(root);
    }
};
#endif /* BST_H */