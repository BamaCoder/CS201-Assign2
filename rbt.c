/*** red-black binary search tree class ***/

#include <stdio.h>
#include "bst.h"
#include "rbst.h"

/*typedef struct rbt*/
/*{*/
  /*bst *tree;*/
  /*void (*display)(FILE *,void *);*/
  /*int (*compare)(void *,void *);*/
  /*int size;*/
  /*int words;*/
/*} rbt;*/

struct rbtval {
    void* value;
    unsigned char color;
    int freq;
} rbtval;

rbt *newRBT(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    rbt *newRBT = malloc(sizeof(rbt));
    if(tree == 0) {
        fprintf(stderr, "out of memory");
        exit(-1);
    }
    newRBT->tree = newBST(displayRBT,c);
    newRBT->display = d;
    newRBT->compare = c;
    newRBT->words = 0;
    newRBT->size = 0;
}
void insertRBT(rbt *rbTree,void *value) {
    rbtval *val = malloc(sizeof(rbtval));
    if(val == 0) {
        fprintf(stderr, "out of memory");
        exit(-1);
    }
    val->value = value;
    val->color = 'r';
    val->freq = 1;

    bstNode *newNode = insertBST(rbTree->tree, val);
    while(1) {
        if(newNode == rbTree->tree->root) break;
        if(newNode->parent->value->color == 'b') break;
        if(newNode->parent->parent->left == newnode->parent) {
            if(newNode->parent->parent->right->value->color == 'r') {
                newNode->parent->value->color = 'b';
                newNode->parent->parent->right->value->color = 'b';
                newNode->parent->parent = 'r';
                newNode = newNode->parent->parent;
            }
        }
        else if(newNode->parent->parent->right == newnode->parent){
            if(newNode->parent->parent->left->value->color == 'r') {
                newNode->parent->value->color = 'b';
                newNode->parent->parent->left->value->color = 'b';
                newNode->parent->parent = 'r';
                newNode = newNode->parent->parent;
            }
        }
        else  {
            if()
        }
extern int findRBT(rbt *,void *);
extern void deleteRBT(rbt *,void *);
extern void statisticsRBT(rbt *,FILE *);
extern void displayRBT(FILE *,rbt *);
extern void checkRBT(rbt *);               //optional
#endif
