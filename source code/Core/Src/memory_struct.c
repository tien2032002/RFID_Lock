#include "memory_struct.h"
#include "global.h"
#include "fsm.h"



struct node* admin=NULL;
struct node* root=NULL;

uint8_t largerID(uint8_t* CardID1, uint8_t* CardID2) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (CardID1[i] > CardID2[i]) return 1;
	}
	return 0;
}

uint8_t equalID(uint8_t* CardID1, uint8_t* CardID2) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (CardID1[i] != CardID2[i]) return 0;
	}
	return 1;
}

void duplicateID(uint8_t* CardID1, uint8_t* CardID2){
    	uint8_t i;
	for (i = 0; i < 5; i++) {
		CardID1[i] = CardID2[i];
	}
}



void inorder_rec(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d \n", root->ID[0]);
        inorder(root->right);
    }
}

void inorder(){
    inorder_rec(root);
}

struct node* newNode(uint8_t *ID)
{
    // Allocate memory for new node
    struct node* node
        = (struct node*)malloc(sizeof(struct node));
  
    for(uint8_t i=0;i<5;i++)
    node->ID[i] = ID[i];
    node->left = node->right = NULL;
    return (node);
}

struct node* minValueNode(struct node* node)
{
    struct node* current = node;
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
  
    return current;
}

struct node* insert_rec(struct node* node, uint8_t *key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);
 
    /* Otherwise, recur down the tree */
    if  (largerID(node->ID,key)) // key < node->ID 
        node->left = insert_rec(node->left, key);
    else if (largerID(key,node->ID)) //key > node->ID
        node->right = insert_rec(node->right, key);
 
    /* return the (unchanged) node pointer */
    return node;
}

struct node* insert(uint8_t* key){
    return insert_rec(root,key);
}

struct node* search_rec(struct node* root, uint8_t *key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || equalID(root->ID, key))
       return root;
    
    // Key is greater than root's key
    if (largerID(key,root->ID)) //(root->ID < key)
       return search_rec(root->right, key);
 
    // Key is smaller than root's key
    return search_rec(root->left, key);
}

uint8_t search(uint8_t* key){
    if (equalID(admin->ID,key)) return 1;
    if (search_rec(root,key)==NULL) return 0;
    else return 1;
}

struct node* deleteNode_rec(struct node* root, uint8_t* key)
{
    // base case
    if (root == NULL)
        return root;
  
    // If the key to be deleted 
    // is smaller than the root's
    // key, then it lies in left subtree
    if (largerID(root->ID,key))//(key < root->ID)
        root->left = deleteNode_rec(root->left, key);
  
    // If the key to be deleted 
    // is greater than the root's
    // key, then it lies in right subtree
    else if (largerID(key,root->ID))//(key > root->ID)
        root->right = deleteNode_rec(root->right, key);
  
    // if key is same as root's key, 
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
  
        // node with two children: 
        // Get the inorder successor
        // (smallest in the right subtree)
        struct node* temp = minValueNode(root->right);
  
        // Copy the inorder 
        // successor's content to this node
        
        //root->ID = temp->ID;
  
        // Delete the inorder successor
        root->right = deleteNode_rec(root->right, temp->ID);
    }
    return root;
}

struct node* deleteNode(uint8_t* key){
    return deleteNode_rec(root,key);
}

uint8_t add_new_card(uint8_t* key,uint8_t* admin_key){
    if(admin==NULL) return 0;
    //check admin card first, if wrong 
    if (equalID(admin_key,admin->ID))
    {
        root=insert(key);
        return 1;
    }
    return 0;
}

void deleteTree_rec(struct node*root){
if (root == NULL) return;
 
    /* first delete both subtrees */
    deleteTree_rec(root->left);
    deleteTree_rec(root->right);
   
    /* then delete the node */
    free(root);

}

uint8_t delete_card(uint8_t* admin_key){
    if(equalID(admin_key,admin->ID))
    { 
        deleteTree_rec(root);
        return 1;
    }
    return 0;
    //state=open_door;

}

uint8_t set_admin(uint8_t* ID){

    if (admin==NULL && state == INIT)
    {
        admin = newNode(ID);
        return 1;
    }
    return 0;
}
