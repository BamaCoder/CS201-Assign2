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
  void (*display)(FILE*,void*);
  int freq;
  unsigned char color;
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
  val->display = d;
  val->color = 'r';
  val->freq = 1;

  bstNode *newNode = insertBST(rbTree->tree, val);
  while(1) {
    if(newNode == rbTree->tree->root) break;
    if(color(newNode->parent) == 'b') break;
    if(color(uncle(newNode)) == 'r') {
      newNode->parent->value->color = 'b';
      uncle(newNode)->value->color = 'b';
      grandparent(newNode)->value->color ='r';
      newNode = grandparent(newNode);
    }
    else {
      if(uncle(newNode) != 0) {
        bstNode *padre = newNode->parent;
        if(isleftChild(newNode)) {
          if(newNode->parent == rbTree->tree->root) {
            newNode->parent = newNode;
            rbTree->tree->root = newNode;
          }
          else newNode->parent = newNode->parent->parent;
          newNode->right = padre;
          padre->left = newNode->right;
          padre->parent = newNode;
        }
        else {
          if(newNode->parent == rbTree->tree->root) {
            newNode->parent = newNode;
            rbTree->tree->root = newNode;
          }
          else newNode->parent = newNode->parent->parent;
          newNode->left = padre;
          padre->right = newNode->left;
          padre->parent = newNode;
        }
        newNode->value->color = 'b';
        newNode->parent->value->color = 'r';
        padre = newNode->parent;
        if(isleftChild(newNode)) {
          if(newNode->parent == rbTree->tree->root) {
            newNode->parent = newNode;
            rbTree->tree->root = newNode;
          }
          else newNode->parent = newNode->parent->parent;
          newNode->right = padre;
          padre->left = newNode->right;
          padre->parent = newNode;
        }
        else {
          if(newNode->parent == rbTree->tree->root) {
            newNode->parent = newNode;
            rbTree->tree->root = newNode;
          }
          else newNode->parent = newNode->parent->parent;
          newNode->left = padre;
          padre->right = newNode->left;
          padre->parent = newNode;
        }
        break;
      }
    }
    rbTree->tree->root->value->color = 'b';
  }
}

int findRBT(rbt *rbTree,void *val) {
  return findBST(rbTree->tree, val);

void deleteRBT(rbt *,void *) return;

int sizeRBT(rbt *rbTree) {
  return rbTree->size;
}

int wordsRBT(rbt *rbTree) {
  return rbTree->words;
}

void statisticsRBT(rbt *rbtTree,FILE *fp) {
  fprintf(fp, "Words/Phrases: %d\n", wordsRBT(rbTree));
  fprintf(fp, "Nodes: %d\n", sizeRBT(rbTree));
  statisticsBST(rbtTree->tree,fp);
}

void displayRBT(FILE *fp,rbt *rbtTree) {
  displayBST(fp, rbtTree->tree);
}

inline bstNode *grandparent(bstNode *x) {
  return x->parent->parent;
}

inline int isleftChild(bstNode *x) {
  return (x == x->parent->left);

bstNode *uncle(bstNode *x) {
  if(x == x->parent->left)
    return grandparent(x)->right;
  else
    return grandparent(x)->left;
}

unsigned char color(bstNode *x) {
  if(x == 0)
    return 'b';
  else
    return x->value->color;
}
