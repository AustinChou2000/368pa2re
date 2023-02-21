#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "struct.h"
#include "unpack.h"
#include "writeoutput.h"

int main (int argc, char** argv){
    if(argc != 5){
        fprintf(stderr, "Incorrect number of arguments!");
        return EXIT_FAILURE;
    }

    FILE* infp = fopen(argv[1], "rb");
    if(infp == NULL){
        fprintf(stderr, "Unable to open input file.\n");
        return EXIT_FAILURE;
    }
    fseek(infp,0,SEEK_END);
    int len = ftell(infp);
    fseek(infp,0,SEEK_SET);
    if(len == 0){
        fprintf(stderr, "The file is empty.\n");
        fclose(infp);
        return EXIT_FAILURE;
    }
    TreeNode* root = unpack(infp);

    if(!writeOutput1(argv[2], root)){
        return EXIT_FAILURE;
    }

    if(!writeOutput2(argv[3], root)){
        return EXIT_FAILURE;
    }

    if(!writeOutput3(argv[4], root)){
        return EXIT_FAILURE;
    }

    destroyTree(root);

    return EXIT_SUCCESS;
}
