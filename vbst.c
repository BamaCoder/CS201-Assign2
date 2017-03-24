/*** red-black binary search tree class ***/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "vbst.h"

/*typedef struct vbst*/
/*{*/
/*bst *tree;*/
/*void (*display)(FILE *,void *);*/
/*int (*compare)(void *,void *);*/
/*int size;*/
/*int words;*/
/*} vbst;*/

typedef struct vbstval {
  void* value;
  void (*display)(FILE*,void*);
  int (*compare)(void*,void*);
  int freq;
  unsigned char color;
} vbstval;

void displayVBSTVal(FILE * fp, void *value) {
    vbstval *v = value;
    v->display(fp, v->value);
    if(v->freq > 1) fprintf(fp, "-%d", v->freq);
}

int compareVBSTVal(void *a, void *b) {
    vbstval *first = a;
    vbstval *second = b;
    return first->compare(first->value,second->value);
}

vbstval *newVBSTVal(void (*d)(FILE *, void*), int(*c)(void*, void*)) {
    vbstval *nodeval = malloc(sizeof(vbstval));
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

vbst *newVBST(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
  vbst *newTree = malloc(sizeof(vbst));
  if(newTree == 0) {
    fprintf(stderr, "out of memory");
    exit(-1);
  }
  newTree->tree = newBST(displayVBSTVal, compareVBSTVal);
  newTree->display = d;
  newTree->compare = c;
  newTree->words = 0;
  newTree->size = 0;
  return newTree;
}

void insertVBST(vbst *vbstree,void *value) {
  vbstval* val = newVBSTVal(vbstree->display, vbstree->compare);
  val->value = value;
  bstNode *findval = findBSTNode(vbstree->tree, val);
  if(findval != 0) {
    ((vbstval*)findval->value)->freq++;
    vbstree->words++;
    return;
  }
  else {
    bstNode* newNode = insertBST(vbstree->tree, val);
    vbstree->words++;
    vbstree->size++;
  }
}

int findVBST(vbst *vbstree,void *val) {
  bstNode *tmp = findBSTNode(vbstree->tree, val);
  if(tmp != 0) return ((vbstval*)tmp->value)->freq;
  else return 0;
}

void deleteVBST(vbst *tree,void *a) {
    bstNode* findval = findBSTNode(tree->tree, a);
    if(findval != 0) {
        if(((vbstval*)findval->value)->freq > 1) {
           ((vbstval*)findval->value)->freq--;
        }
        findval = swapToLeafBSTNode(findval);
        pruneBSTNode(tree->tree, findval);
    }
    else {
        return;
    }
}

int sizeVBST(vbst *vbstree) {
  return vbstree->size;
}

int wordsVBST(vbst *vbstree) {
  return vbstree->words;
}

void statisticsVBST(vbst *vbstTree,FILE *fp) {
  fprintf(fp, "Words/Phrases: %d\n", wordsVBST(vbstTree));
  fprintf(fp, "Nodes: %d\n", sizeVBST(vbstTree));
  statisticsBST(vbstTree->tree,fp);
}

void displayVBST(FILE *fp,vbst *vbstTree) {
  displayBST(fp, vbstTree->tree);
}

