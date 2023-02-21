#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "struct.h"
#include "unpack.h"
#include "helper.h"

TreeNode* unpack(FILE* fp){
    NodeTop* s = malloc(sizeof(NodeTop));
    s -> top = NULL;

    do{
        char c = '\0';
        fread(&c, sizeof(char), 1, fp);
        if(feof(fp)){
            if(s->top->next == NULL) break;
            fprintf(stderr, "Invalid input format, unable to construct a tree with stack.\n");
            destroyList(s);
            fclose(fp);
            return NULL;
        }
        if(c == 'H' || c == 'V'){  
            Node* nd1 = pop(s);
            Node* nd2 = pop(s);
            TreeNode* tn = buildTreeNode(0, c, NULL, 0, NULL, 0, 0, 0);
            tn -> right = nd1 -> tnptr;
            tn -> left = nd2 -> tnptr;
            free(nd1);
            free(nd2);
            push(tn, s);
            fread(&c, sizeof(char), 1, fp);
        } else if(c >= '0' || c <= '9'){
            char* dim = malloc(sizeof(char)*30);
            long count;
            int lablen;
            int width;
            int length;
            char* label = readNumbers(fp, dim, c, &count, &lablen, &width, &length);
            push(buildTreeNode(1, 'N', label, lablen, dim, count, width, length), s);
        }
    } while(!isEmptyStack(s));


    TreeNode* root = s -> top -> tnptr;
    free(s->top);
    free(s);
    fclose(fp);
    return root;
}

void push(TreeNode* tn, NodeTop* tp){
    Node* nd = buildListNode(tn);
    if(tp == NULL){
        tp->top = nd;
        return;
    }

    if(tn->leaf == 0) writeDim(tn);

    nd -> next = tp->top;
    tp->top = nd;
}

Node* pop(NodeTop* s){
    Node* rtv = s -> top;
    s -> top = s -> top -> next;

    return rtv;
}

bool isEmptyStack(NodeTop* s){
    if(s->top == NULL){
        return true;
    }
    return false;
}

char* readNumbers(FILE* fp, char* dim, char c1, long* cnt, int* lablen, int* width, int* length){
    char c = '\0';
    long count = 0;
    char readInt[8] = {'\n'};
    int idx = 0; 

    readInt[0] = c1;
    c = fgetc(fp);
    idx++;
    while(c != '('){
        readInt[idx] = c;
        idx++;
        c = fgetc(fp);
    }
    char* label = malloc(sizeof(char)*(idx+1));
    strncpy(label, readInt, idx);
    label[idx] = '\n';
    *lablen = idx+1;
    memset(readInt, 0, sizeof(readInt));
    dim[count] = c;
    count++;
    idx = 0;
    do{
        c = fgetc(fp);
        dim[count] = c;
        if(c == ','){
            idx = 0;
            *width = atoi(readInt);
            memset(readInt, 0, sizeof(readInt));
        } else if (c == ')'){
            idx = 0;
            *length = atoi(readInt);
            memset(readInt, 0, sizeof(readInt));
        }
        readInt[idx] = c;
        if(c == ',') idx--;
        idx++;
        count++;
    }while(c != '\n');

    dim[count] = '\0';
    count++;

    *cnt = count;

    return label;
}

TreeNode* buildTreeNode(int leaf, char c, char* label, int lablen, char* dim, long count, int width, int length){
    TreeNode* root = malloc(sizeof(TreeNode));
    if(root == NULL){
        fprintf(stderr, "Unable to malloc a treenode.\n");
        return NULL;
    }
    root -> leaf = leaf;
    root -> c = c;
    root -> dim = NULL;
    root -> label = NULL;
    if(label != NULL){
        root->label = malloc(sizeof(char)*lablen);
        strncpy(root->label, label, lablen);
        free(label);
    }
    if(leaf == 1){
        root->dim = malloc(sizeof(char)*count);
	    strncpy(root->dim, dim, count);
        free(dim);
    }
    root -> width = width;
    root -> length = length;
    root -> left = NULL;
    root -> right = NULL;

    return root;
}

Node* buildListNode(TreeNode* tn){
    Node* nd = malloc(sizeof(Node));
    if(nd == NULL){
        fprintf(stderr, "Unable to malloc a list node.\n");
        return NULL;
    }

    nd -> tnptr = tn;
    nd -> next = NULL;
    return nd;
}

void destroyList(NodeTop* tp){
    destroyTree(tp->top->tnptr);

    free(tp->top);
    free(tp);
}

void destroyTree(TreeNode* root){
    if(root == NULL){
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    free(root->label);
    free(root->dim);
    free(root);
}
