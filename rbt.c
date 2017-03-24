/*** red-black binary search tree class ***/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "rbt.h"

/*typedef struct rbt*/
/*{*/
/*bst *tree;*/
/*void (*display)(FILE *,void *);*/
/*int (*compare)(void *,void *);*/
/*int size;*/
/*int words;*/
/*} rbt;*/

typedef struct rbtval {
  void* value;
  void (*display)(FILE*,void*);
  int (*compare)(void*,void*);
  int freq;
  unsigned char color;
} rbtval;

void displayRBTVal(FILE * fp, void *value) {
    rbtval *v = value;
    v->display(fp, v->value);
    if(v->freq > 1) fprintf(fp, "-%d", v->freq);
    fprintf(fp, "-%c", v->color);
}

bstNode *grandparent(bstNode *x) {
  return x->parent->parent;
}

int isleftChild(bstNode *x) {
  return (x == x->parent->left);
}

int isLinear(bstNode *x) {
    if(isleftChild(x) && isleftChild(x->parent)) return 1;
    else if(!isleftChild(x) && !isleftChild(x->parent)) return 1;
    else return 0;
}

void rightRotate(rbt *rbTree, bstNode *child, bstNode *parent) {
    //printf("Rotating right: \n");
     /*displayRBTVal(stdout, child->value);*/
    //printf(" to ");
    /*displayRBTVal(stdout, parent->value);*/
    //printf("\n");
    parent->left = child->right;
    if(child->right != 0) child->right->parent = parent;
    if(parent != rbTree->tree->root) child->parent = parent->parent;
    else {
        child->parent = child;
        rbTree->tree->root = child;
        parent->parent =child;
    }
    if(isleftChild(parent)) {
        if(parent->parent != child) {
            parent->parent->left = child;
            parent->parent = child;
        }
    }
    else {
        if(parent->parent != child) {
            parent->parent->right = child;
        }
    }
    child->right = parent;
}

void leftRotate(rbt *rbTree, bstNode *child, bstNode *parent) {
    //printf("Rotating left: \n");
    /*displayRBTVal(stdout, child->value);*/
    //printf(" to ");
    /*displayRBTVal(stdout, parent->value);*/
    //printf("\n");
    parent->right = child->left;
    if(child->left != 0) child->left->parent = parent;
    if(parent != rbTree->tree->root) {
        child->parent = parent->parent;
    }
    else {
        child->parent = child;
        rbTree->tree->root = child;
        parent->parent = child;
    }
    if(isleftChild(parent)) {
        if(parent->parent != child) {
            parent->parent->left = child;
            parent->parent = child;
        }
    }
    else {
        if(parent->parent != child) {
            parent->parent->right = child;
            parent->parent = child;
        }
    }
    child->left = parent;
}


bstNode *uncle(bstNode *x) {
  if(isleftChild(x->parent))
    return grandparent(x)->right;
  else
    return grandparent(x)->left;
}

unsigned char color(bstNode *x) {
  if(x == 0)
    return 'B';
  else
    return ((rbtval*)x->value)->color;
}


int compareRBTVal(void *a, void *b) {
    rbtval *first = a;
    rbtval *second = b;
    return first->compare(first->value,second->value);
}

rbtval *newRBTVal(void (*d)(FILE *, void*), int(*c)(void*, void*)) {
    rbtval *nodeval = malloc(sizeof(rbtval));
    if(nodeval == 0) {
        fprintf(stderr, "out of memory");
        exit(-1);
    }
    nodeval->display = d;
    nodeval->compare = c;
    nodeval->color = 'B';
    nodeval->freq = 1;
    return nodeval;
}

rbt *newRBT(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
  rbt *newTree = malloc(sizeof(rbt));
  if(newTree == 0) {
    fprintf(stderr, "out of memory");
    exit(-1);
  }
  newTree->tree = newBST(displayRBTVal, compareRBTVal);
  newTree->display = d;
  newTree->compare = c;
  newTree->words = 0;
  newTree->size = 0;
  return newTree;
}

void insertRBT(rbt *rbTree,void *value) {
  rbtval* val = newRBTVal(rbTree->display, rbTree->compare);
  val->value = value;
  bstNode* findval = findBSTNode(rbTree->tree, val);
  if(findval != 0) {
//    fprintf(stdout, "\n String %s found. Increasing Freq \n", (char*)((rbtval*)findval->value)->value);
    ((rbtval*)findval->value)->freq++;
    rbTree->words++;
    return;
  }
  else {
      val->color = 'R';
      bstNode *newNode = insertBST(rbTree->tree, val);
      rbTree->size++;
      rbTree->words++;
      while(1) {
        bstNode *parental = newNode->parent;
        bstNode *uncs = uncle(newNode);
        bstNode *gramps = grandparent(newNode);
        if(newNode == rbTree->tree->root) break;
        if(color(parental) == 'B') break;
        if(color(uncs) == 'R') {
          ((rbtval*)parental->value)->color = 'B';
          ((rbtval*)uncs->value)->color = 'B';
          ((rbtval*)gramps->value)->color ='R';
          newNode = gramps;
        }
        else {
          //printf("\n Current Tree form: \n");
          //displayRBT(stdout, rbTree);
          //printf("\n");
          if(isLinear(newNode) == 0) {
            bstNode *oldnode = newNode;
            bstNode *oldparent = parental;
            if(isleftChild(newNode)) rightRotate(rbTree, newNode, parental);
            else leftRotate(rbTree, newNode, parental);
            newNode = oldparent;
            parental = oldnode;
          }
          ((rbtval*)parental->value)->color = 'B';
          ((rbtval*)gramps->value)->color = 'R';
          if(isleftChild(parental)) rightRotate(rbTree,parental,gramps);
          else leftRotate(rbTree, parental, gramps);
          break;
        }
      }
      ((rbtval*)rbTree->tree->root->value)->color = 'B';
      //printf("\n Current Tree form: \n");
      //displayRBT(stdout, rbTree);
      //printf("\n");
  }
}

int findRBT(rbt *rbTree,void *val) {
  bstNode *tmp = findBSTNode(rbTree->tree, val);
  if(tmp != 0) return ((rbtval*)tmp->value)->freq;
  else return 0;
}

void deleteRBT(rbt *tree,void *a) {return;}

int sizeRBT(rbt *rbTree) {
  return rbTree->size;
}

int wordsRBT(rbt *rbTree) {
  return rbTree->words;
}

void statisticsRBT(rbt *rbtTree,FILE *fp) {
  fprintf(fp, "Words/Phrases: %d\n", wordsRBT(rbtTree));
  fprintf(fp, "Nodes: %d\n", sizeRBT(rbtTree));
  statisticsBST(rbtTree->tree,fp);
}

void displayRBT(FILE *fp,rbt *rbtTree) {
  displayBST(fp, rbtTree->tree);
}

