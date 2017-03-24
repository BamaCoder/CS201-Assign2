/*** common binary search tree class ***/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "queue.h"

bst *newBST(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
  bst *newTree = malloc(sizeof(bst));
  if(newTree == 0) {
    fprintf(stderr, "out of memory");
    exit(-1);
  }
  newTree->root = 0;
  newTree->display = d;
  newTree->compare = c;
  return newTree;
}

bstNode *insertBST(bst *tree,void *value) {
  bstNode *curnode = tree->root;
  bstNode *newnode = malloc(sizeof(bstNode));
  if(newnode == 0) {
    fprintf(stderr, "out of memory");
    exit(-1);
  }
  newnode->value = value;
  newnode->left = 0;
  newnode->right = 0;
  if(tree->root == 0) {
    newnode->parent = newnode;
    tree->root = newnode;
  }
  else {
    while(1) {
      int valComp = tree->compare(newnode->value, curnode->value);
      if(valComp <  0 ) {
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

int findBST(bst *tree,void *value) {
  bstNode *curnode = tree->root;
  if(curnode == 0) return 0;
  while(1) {
    if(tree->compare(value,curnode->value)==0) return 1;
    else if (tree->compare(value,curnode->value) < 0)  {
        if(curnode->left == 0)
            return 0;
        else
            curnode = curnode->left;
    }
    else {
        if(curnode->right == 0)
            return 0;
        else
            curnode = curnode->right;
    }
  }
}

bstNode *findBSTNode(bst *tree,void *value) {
  bstNode *curnode = tree->root;
  if(curnode == 0) return 0;
  while(1) {
    int notEqual = tree->compare(value,curnode->value);
    if(notEqual == 0) return curnode;
    else if (notEqual < 0)  {
        if(curnode->left == 0)
            return 0;
        else
            curnode = curnode->left;
    }
    else {
        if(curnode->right == 0)
            return 0;
        else
            curnode = curnode->right;
    }
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
    return swapToLeafBSTNode(iter);
  }
  else {
    iter = n->right;
    while(iter->left != 0)
      iter = iter->left;
    temp = iter->value;
    iter->value = n->value;
    n->value = temp;
    return swapToLeafBSTNode(iter);
  }
}

void pruneBSTNode(bst *tree, bstNode *n) {
  if((n->parent->left == 0 && n->parent->right == 0)) {
    n = 0;
  }
  else if(n->left == 0 && n->right == 0) {
    if(n == n->parent->left) {
      n->parent->left = 0;
    }
    else {
      n->parent->right = 0;
    }
  }
  else {
    n = swapToLeafBSTNode(n);
    pruneBSTNode(tree, n);
  }
}

void statisticsBST(bst *tree,FILE *fp) {
  queue *q = newQueue(tree->display);
  unsigned int lev = 0, maxdepth = 0, mindepth = 0;
  unsigned char lowestLeaf = 1;
  if(tree->root != 0) {
    enqueue(q, tree->root);
    while(sizeQueue(q)) {
      for(int i = 0, n = sizeQueue(q); i < n; i++) {
        bstNode *iter = peekQueue(q);
        if(lowestLeaf && (iter->left == 0 && iter->right == 0)) {
          mindepth = lev;
          lowestLeaf = 0;
        }
        dequeue(q);
        if(iter->left  != 0)
          enqueue(q, iter->left);
        if(iter->right != 0)
          enqueue(q, iter->right);
      }
      lev++;
    }
    maxdepth = lev;
  }
  fprintf(fp, "Minimum depth: %u\n", mindepth);
  fprintf(fp, "Maximum depth: %u\n", maxdepth);
}

void displayBST(FILE *fp,bst *tree) {
  if(tree->root == 0) {
    fprintf(fp, "0: \n");
    return;
  }
  queue *q = newQueue(tree->display);
  int lev = 0;
  enqueue(q, tree->root);
  while(1) {
    int n = sizeQueue(q);
    fprintf(fp, "%d: ", lev);
    lev++;
    while(n > 0) {
      bstNode *iter = peekQueue(q);
      if(iter->left == 0 && iter->right == 0) fprintf(fp, "=");
      tree->display(fp, iter->value);
      fprintf(fp, "(");
      tree->display(fp, iter->parent->value);
      fprintf(fp, ")-");
      if(iter->parent->left == iter) fprintf(fp, "l");
      else if(iter->parent->right == iter) fprintf(fp, "r");
      dequeue(q);
      if(iter->left  != 0)
        enqueue(q, iter->left);
      if(iter->right != 0)
        enqueue(q, iter->right);
      n--;
      if(n > 0) fprintf(fp, " ");
    }
    fprintf(fp, "\n");
    if(n == 0) break;
  }
}
