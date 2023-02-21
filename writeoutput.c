#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "struct.h"
#include "writeoutput.h"
#include "helper.h"

bool writeOutput1(char* outfile, TreeNode* tn){
    FILE* fp = fopen(outfile, "wb");

    if(fp == NULL){
        return false;
    }

    if(printPre(fp, tn)){
        fclose(fp);
        return true;
    }

    fprintf(stderr, "Problems with writing output one.\n");
    fclose(fp);
    return false;
}

bool writeOutput2(char* outfile, TreeNode* tn){
    FILE* fp = fopen(outfile, "wb");

    if(fp == NULL){
        return false;
    }

    if(printPost(fp, tn)){
        fclose(fp);
        return true;
    }

    fprintf(stderr, "Problems with writing output three.\n");
    fclose(fp);
    return false;
}

bool writeOutput3(char* outfile, TreeNode* tn){
    FILE* fp = fopen(outfile, "wb");

    if(fp == NULL){
        fprintf(stderr, "Unable to open output file three.\n");
        return false;
    }

    printCoor(fp, tn, 0, 0);

    fclose(fp);
    return true;
}

bool printPre(FILE* fp, TreeNode* root){
    if(root -> leaf == 1){
        int count = 0;
        while(1){
            fwrite(&root->label[count], sizeof(char), 1, fp);
            count++;
            if(root->label[count] == '\n') break;
        }
        count = 0;
        while(1){
            fwrite(&root->dim[count], sizeof(char), 1, fp);
            count++;
            if(root->dim[count] == '\n') break;
        }
        fwrite(&root->dim[count], sizeof(char), 1, fp);
        return true;
    }

    if(root->leaf == 0){
        fwrite(&root->c, sizeof(char), 1, fp);
        char c = '\n';
        fwrite(&c, sizeof(char), 1, fp);
    }
    if(!printPre(fp, root->left)){
        fprintf(stderr, "Error traversing to left child.\n");
        return false;
    }
    if(!printPre(fp, root->right)){
        fprintf(stderr, "Error traversing to right child.\n");
        return false;
    }
    return true;
}

bool printPost(FILE* fp, TreeNode* root){
    if(root -> leaf == 1){
        int count = 0;
        while(1){
            fwrite(&root->label[count], sizeof(char), 1, fp);
            count++;
            if(root->label[count] == '\n') break;
        }
        count = 0;
        while(1){
            fwrite(&root->dim[count], sizeof(char), 1, fp);
            count++;
            if(root->dim[count] == '\n') break;
        }
        fwrite(&root->dim[count], sizeof(char), 1, fp);
        return true;
    }

    if(!printPost(fp, root->left)){
        fprintf(stderr, "Error traversing to left child.\n");
        return false;
    }
    if(!printPost(fp, root->right)){
        fprintf(stderr, "Error traversing to right child.\n");
        return false;
    }
    if(root->leaf == 0){
        int count =0;
        fwrite(&root->c, sizeof(char), 1, fp);
        while(1){
            fwrite(&root->dim[count], sizeof(char), 1, fp);
            count++;
            if(root->dim[count] == '\n') break;
        }
        fwrite(&root->dim[count], sizeof(char), 1, fp);
        return true;
    }
    return false;
}

void printCoor(FILE* fp, TreeNode* root, int width, int length){
    if(root->leaf == 1){
        int count = 0;
        char c = '(';
        while(1){
            fwrite(&root->label[count], sizeof(char), 1, fp);
            count++;
            if(root->label[count] == '\n') break;
        }
        fwrite(&c, sizeof(char), 1, fp);
        count = 0;
        while(1){
            fwrite(&root->dim[count], sizeof(char), 1, fp);
            count++;
            if(root->dim[count] == '\n') break;
        }
        printIntToStr(fp, root, width, length);
        c = ')';
        fwrite(&c, sizeof(char), 1, fp);
        c = '\n';
        fwrite(&c, sizeof(char), 1, fp);
        return;
    }

    if(root->c == 'H'){
        length += root->right->length;
    }
    printCoor(fp, root->left, width, length);
    if(root->c == 'V'){
        width += root->left->width;
    }
    if(root->c == 'H'){
        length -= root->right->length;
    }
    printCoor(fp, root->right, width, length);
}
