#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;

template <typename ct>
class BSTNode{
  public:
	ct* data;
    int height = 1;
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
	ct* search(ct* val){
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
        if(loc){
            return loc->data;
        }
        return NULL;
	}
    int height(BSTNode<ct>* curr){
        if(curr == NULL){
            return 0;
        }
        return curr->height;
    }
    int difference(BSTNode<ct>* curr){
        if(curr == NULL){
            return 0;
        }
        int lHeight = height(curr->leftChild);
        int rHeight = height(curr->rightChild);
        curr->height = 1 + max(lHeight,rHeight);
        return lHeight - rHeight;
    }
    BSTNode<ct>* rRotate(BSTNode<ct>* curr){
        BSTNode<ct>* newRoot = curr->leftChild;
        curr->leftChild = newRoot->rightChild;
        newRoot->rightChild = curr;
        difference(curr);
        difference(newRoot);
        return newRoot;
    }
    BSTNode<ct>* lRotate(BSTNode<ct>* curr){
        BSTNode<ct>* newRoot = curr->rightChild;
        curr->rightChild = newRoot->leftChild;
        newRoot->leftChild = curr;
        difference(curr);
        difference(newRoot);
        return newRoot;
    }
    BSTNode<ct>* lrRotate(BSTNode<ct>* curr){
        curr->leftChild = lRotate(curr->leftChild);
        curr = rRotate(curr);
        return curr;
    }
    BSTNode<ct>* rlRotate(BSTNode<ct>* curr){
        curr->rightChild = rRotate(curr->rightChild);
        curr = lRotate(curr);
        return curr;
    }
    BSTNode<ct>* balance(BSTNode<ct>* curr){
        int balFactor = difference(curr);
        if(balFactor > 1){
            if(difference(curr->leftChild) >= 0){
                curr = rRotate(curr);
            }
            else{
                curr = lrRotate(curr);
            }
        }
        else if(balFactor < -1){
            if(difference(curr->leftChild) <= 0){
                curr = lRotate(curr);
            }
            else{
                curr = rlRotate(curr);
            }
        }
        return curr;
    }
    void insertWithoutDuplication(ct* val){
		if(root == NULL){
            BSTNode<ct>* nn = new BSTNode<ct>();
            nn->data = val;
            root = nn;
            return;
        }
        if(root->data->id >= val->id){
            root->leftChild = insertWithoutDuplication(val,root->leftChild);
        }
        else{
            root->rightChild = insertWithoutDuplication(val,root->rightChild);
            
        }
        root = balance(root);
    }
	BSTNode<ct>* insertWithoutDuplication(ct* val,BSTNode<ct>* curr){
		if(curr == NULL){
            BSTNode<ct>* nn = new BSTNode<ct>();
            nn->data = val;
            return nn;
        }
        if(curr->data->id >= val->id){
            curr->leftChild = insertWithoutDuplication(val,curr->leftChild);
        }
        else{
            curr->rightChild = insertWithoutDuplication(val,curr->rightChild);
            
        }
        curr = balance(curr);
        return curr;
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