/*** common binary search tree class ***/

#include <stdio.h>
#include "bst.h"
#include "queue.h"

/*typedef struct bstNode*/
/*{*/
/*struct bstNode *left;*/
/*struct bstNode *right;*/
/*struct bstNode *parent;*/
/*void *value;*/
/*} bstNode;*/

/*typedef struct bst*/
/*{*/
/*bstNode *root;*/
/*void (*display)(FILE *,void *);*/
/*int (*compare)(void *,void *);*/
/*} bst;*/

bst *newBST(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
  bst *newTree = malloc(sizeof(bst)):
    if(newTree == 0) {
      fprintf(stderr, "out of memory");
      exit(-1);
    }
  newTree->root = 0;
  newTree->display = d;
  newTree->compare = c;
}

bstNode *insertBST(bst *tree,void *value) {
  bstNode *curnode = tree->root;
  bstNode *newnode = malloc(sizeof(bstNode));
  newnode->value = value;
  newnode->left = 0;
  newnode->right = 0;
  if(curnode == 0) {
    newnode->parent = 0;
    tree->root = newnode;
  }
  else {
    while(1) {
      if(newnode->value < curnode->value) {
        if(curnode->left == 0) {
          curnode->left = newnode;
          newnode->parent = curnode;
          break;
        }
        else curnode = curnode->left;
      }
      else {
        if(curnode->right == 0) {
          curnode->right = newnode;
          newnode->parent = curnode;
          break;
        }
        else curnode = curnode->right;
      }
    }
  }
  return newnode;
}

}

int findBST(bst *tree,void *value) {
  bstNode curnode = tree->root;
  if(curnode == 0) return 0;
  while(1) {
    if(value == curnode->value) return 1;
    else if (value < curnode->value) curnode = curnode->left;
    else curnode = curnode->right;
    if(curnode == 0) return 0;
  }
}

bstNode *findBSTNode(bst *tree,void *value) {
  bstNode curnode == tree->root;
  if(curnode == 0) return 0;
  while(1) {
    if(value == curnode->value) return curnode;
    else if (value < curnode->value) curnode = curnode->left;
    else curnode = curnode->right;
    if(curnode == 0) return 0;
  }
}

bstNode *swapToLeafBSTNode(bstNode *n){
  void *temp = 0;
  bstNode *iter = n;
  if(n->left == 0 && n->right == 0)
    return n;
  else if (n->left != 0) {
    iter = n->left;
    while(iter->right != 0)
      iter = iter ->right;
    temp = iter->value;
    iter->value = n->value;
    n->value = temp;
    swapToLeafBSTNode(iter);
  }
  else {
    iter = n->right;
    while(iter->left != 0)
      iter = iter->left;
    temp = iter->value;
    iter->value = n->value;
    n->value = temp;
    swapToLeafBSTNode(current);
  }
}

void pruneBSTNode(bstNode *n) {
  if((n->parent->left == 0 && n->parent->right == 0)) {
    n = 0;
    free(n);
  }
  else if(n->left == 0 && n->right == 0) {
    if(n == n->parent->left) {
      n->parent->left = 0;
      free(n->parent->left);
    }
    else {
      n->parent->right = 0;
      free(n->parent->right);
    }
  }
  else {
    n = swapToLeafBSTNode(n);
    pruneBSTNode(n);
  }
}

void statisticsBST(bst *tree,FILE *fp) {
  queue *q = 
  bstNode *iter = tree->root;
extern void displayBST(FILE *fp,bst *tree);
extern void checkBST(bst *tree);                //optional
#endif
