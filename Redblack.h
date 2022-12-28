#ifndef Redblack_H
#define Redblack_H
#include <iostream>
using namespace std;

template <typename ct>
class RBBSTNode{
  public:

	ct* data;  
    //New notes are always red
    bool isBlack = false;
    bool isLeftChild = false;
    //NULL nodes are always black
    //No consecutive red nodes
	RBBSTNode<ct>* leftChild = NULL;
	RBBSTNode<ct>* rightChild = NULL;
    RBBSTNode<ct>* parent = NULL;
};

template <typename ct>
class RBBST{

  public:
    int size = 0;
	RBBSTNode<ct>* root = NULL;
	RBBSTNode<ct>* loc = NULL;
	RBBSTNode<ct>* ploc = NULL;

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
		RBBSTNode<ct>* nn = new RBBSTNode<ct>();
        nn->data = val;
        nn->parent = ploc;
        size++;

        if(ploc == NULL){
            //root is always black!
            nn->isBlack = true;
            root = nn;
            return;
        }
        
        if(ploc->data->id >= val->id){
            ploc->leftChild = nn;
            nn->isLeftChild = true;
        }
        else{
            ploc->rightChild = nn;
        }
        //check if redblack tree is vioed or not?
        check(loc);
        return;
    }

    void check(RBBSTNode<ct>* curr){
        if(curr == root){
            return;
        }
        if(curr->parent->parent != NULL && !curr->isBlack && !curr->parent->isBlack){
            correctTree(curr);
            check(curr->parent);
        }

    }
    
    void correctTree(RBBSTNode<ct>* curr){
        ploc = curr->parent;
        if(ploc->isLeftChild){//if parent is rightChild
            //rotate if sibling of parent is black
            if(ploc->parent->rightChild == NULL || ploc->parent->isBlack){
                rotate(curr);
                return;
            }
            //color flip if sibling of parent isnt black
            if(ploc->parent->rightChild != NULL){
                ploc->parent->rightChild->isBlack = true;
            }
            ploc->parent->isBlack = false;
            ploc->isBlack = true;
            return;
        }
        else{//if parent is rightChild
            //rotate if sibling of parent is black
            if(ploc->parent->leftChild == NULL || ploc->parent->isBlack){
                rotate(curr);
                return;
            }
            //color flip if sibling of parent isnt black
            if(ploc->parent->leftChild != NULL){
                ploc->parent->leftChild->isBlack = true;
            }
            ploc->parent->isBlack = false;
            ploc->isBlack = true;
            return;
        }
    }
    
    void rotate(RBBSTNode<ct>* curr){
        if(curr->isLeftChild){
            if(curr->parent->isLeftChild){//is left child of left child so rotate right and color correct
                rightRotate(curr->parent->parent);
                //parent becomes black, sibling and itself red
                curr->isBlack = false;
                curr->parent->isBlack = true;
                if(curr->parent->rightChild){
                    curr->isBlack = false;    
                }
                return;
            }
            //left right rotate
            leftRotate(curr->parent);
            rightRotate(curr->parent->parent);
            //color correct
            curr->isBlack = false;
            curr->rightChild->isBlack = true;
            curr->leftChild->isBlack = true;
        }
        else{
            if(!curr->parent->isLeftChild){//is right child of right child so rotate right and color correct
                leftRotate(curr->parent->parent);
                //parent becomes black, sibling and itself red
                curr->isBlack = false;
                curr->parent->isBlack = true;
                if(curr->parent->leftChild){
                    curr->isBlack = false;    
                }
                return;
            }
            //right left rotate
            rightRotate(curr->parent);
            leftRotate(curr->parent->parent);
            //color correct
            curr->isBlack = false;
            curr->rightChild->isBlack = true;
            curr->leftChild->isBlack = true;
        }
    }    
    
    void leftRotate(RBBSTNode<ct>* curr){
        loc = curr->rightChild;
        //step 1
        loc->parent = curr->parent;  
        if(!loc->parent){
            root = loc;
        }

        //step 2
        curr->rightChild = loc->leftChild;
        if(curr->rightChild){
            curr->rightChild->parent = curr;
            curr->rightChild->isLeftChild = false; 
        }

        //step 3
        loc->leftChild = curr;
        curr->parent = loc;
        curr->isLeftChild = true;
        
    }
    
    void rightRotate(RBBSTNode<ct>* curr){
        loc = curr->leftChild;
        //step 1
        loc->parent = curr->parent;  
        if(!loc->parent){
            root = loc;
        }

        //step 2
        curr->leftChild = loc->rightChild;
        if(curr->leftChild){
            curr->leftChild->parent = curr; 
        }

        //step 3
        loc->rightChild = curr;
        curr->parent = loc;
        
    }

    void inorder(){
        if(root == NULL){
        return;
        }
        inorder(root->leftChild);
        cout<<root->data<<endl;
        inorder(root->rightChild);
    }
    
    void inorder(RBBSTNode<ct>* curr){
        if(curr == NULL){
        return;
        }
        inorder(curr->leftChild);
        cout<<curr->data<<endl;
        inorder(curr->rightChild);
    } 
    ct biggestval(){
        RBBSTNode<ct>* temp = root;
        while(temp->rightChild != NULL){
        temp = temp->rightChild;
        }
        return temp->data;
    }
    ct smallestval(){
        RBBSTNode<ct>* temp = root;
        while(temp->leftChild != NULL){
        temp = temp->leftChild;
        }
        return temp->data;
    }
    void printLeaf(RBBSTNode<ct>* curr){
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

    int depthOfTree(RBBSTNode<ct>* curr){
        if(curr == NULL){
        return -1;
        }
        return 1 + max(depthOfTree(curr->rightChild),depthOfTree(curr->leftChild)); 
    }
    int heightOfTree(RBBSTNode<ct>* curr,int cHeight){
        if(curr == NULL){
        return cHeight;
        }
        return max(heightOfTree(curr->rightChild,cHeight+1),heightOfTree(curr->leftChild,cHeight+1));
    }
    void destroyNode(RBBSTNode<ct>* curr){
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
#endif /* Redblack_H */