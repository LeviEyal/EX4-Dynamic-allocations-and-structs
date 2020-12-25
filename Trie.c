#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_LETTERS 26
#define WORD 30

typedef struct Node{
    char letter;
    int ends;
    struct Node* children[NUM_LETTERS];
    char* word;
} Node;


Node* newNode(char c){
    Node* p = (Node*)malloc(sizeof(Node));
    if(p == NULL){
        printf("ERROR");
        exit(1);
    }
    p->letter = c;
    return p;
}

void addWord(Node* root, char* s){
    char* word = s;
    while(*s){
        char current = tolower(*s);
        if(root->children[current-'a'] == NULL)
            root->children[current-'a'] = newNode(current);
        root = root->children[current-'a'];
        s++;
        if(!*s){
            root->ends++;
            root->word = word;
        }
    }
}

void printTrie(Node* root){
    if(root == NULL) return;
    if(root->ends){
        printf("%s\t%d\n", root->word, root->ends);
    }
    for (int i = 0; i < NUM_LETTERS; i++){
        printTrie(root->children[i]);
    }  
}

void printTrie_r(Node* root){
    if(root == NULL) return;
    for (int i = NUM_LETTERS-1 ; i >= 0; i--){
        printTrie_r(root->children[i]);
    }  
    if(root->ends){
        printf("%s\t%d\n", root->word, root->ends);
    }
}

void freeTrie(Node* root){
    if(root == NULL) return;
    if(root->ends){
        free(root->word);
    }
    for (int i = 0; i < NUM_LETTERS; i++){
        freeTrie(root->children[i]);
    }
    free(root);
}

int main(int argc, char const *argv[])
{
    Node* root = newNode(0);
    char c;
    int i = 0;
    char* str = (char*)malloc(WORD);
    while((c = getchar()) != EOF)
    {
        if(isspace(c)){
            str[i] = 0;
            addWord(root, str);
            if(c == '\n')
                break;
            i=0;
            str = (char*)malloc(WORD);
            if(str == NULL){
                printf("ERROR");
                exit(1);
            }
        }
        else if(isalpha(c)){
            c = tolower(c);
            str[i] = c;
            i++;
        }
    }

    if(argc == 1)
        printTrie(root);
    else if(argc == 2 && strcmp(argv[1],"r")==0)
        printTrie_r(root);

    freeTrie(root);
    return 0;
}
