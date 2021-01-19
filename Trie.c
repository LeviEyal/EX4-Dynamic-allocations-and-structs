
/****************************************************************************
* Eyal Levi ID.203249073
* Assignment number 4
* https://github.com/LeviEyal
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_LETTERS 26

typedef struct Node{
    char letter;
    int ends;
    struct Node* children[NUM_LETTERS];
    int pos;
} Node;

//=============================== Adding new Node ====================================
Node* newNode(char c){
    Node* p = (Node*)malloc(sizeof(Node));
    if(p != NULL)
        p->letter = c;
    return p;
}
//=============================== Adding new word ====================================
int addWord(Node* root, char* s){
    int i = -1;
    while(*s){
        char current = tolower(*s);
        Node* p = newNode(current);
        if(p == NULL)
            return 0;
        if(root->children[current-'a'] == NULL){
            root->children[current-'a'] = p;
            root->pos = i;
        }
        root = root->children[current-'a'];
        s++;
        i++;
        if(!*s){
            root->ends++;
            root->pos = i;
        }
    }
    return 1;
}
//================================== Print trie ======================================
void printTrie(Node* root, char *str){
    if(root == NULL) return;
    str[root->pos] = root->letter;
    if(root->ends){
        str[root->pos + 1] = 0;
        printf("%s %d\n", str, root->ends);
    }
    for (int i = 0; i < NUM_LETTERS; i++){
        printTrie(root->children[i], str);
    }  
}
//============================= Print trie reversed ==================================
void printTrie_r(Node* root, char *str){
    if(root == NULL) return;
    str[root->pos] = root->letter;
    for (int i = NUM_LETTERS-1 ; i >= 0; i--){
        printTrie_r(root->children[i], str);
    }  
    if(root->ends){
        str[root->pos + 1] = 0;
        printf("%s %d\n", str, root->ends);
    }
}
//=============================== Free trie memory ====================================
void freeTrie(Node* root){
    if(root == NULL) return;
    for (int i = 0; i < NUM_LETTERS; i++){
        freeTrie(root->children[i]);
    }
    free(root);
}
//===================================== MAIN ==========================================
int main(int argc, char const *argv[])
{
    Node* root = newNode(0);
    if(root == NULL) exit(1);
    int i = 0;
    char *str = (char*)malloc(1);
    if(str == NULL){
        freeTrie(root);
        exit(1);
    }
    while(1)
    {
        char c = getchar();
        if(isspace(c) || c == EOF){
            str = realloc(str, i+1);
            if(str == NULL){
                freeTrie(root);
                exit(1);
            }
            str[i] = 0;
            if(addWord(root, str) == 0){
                freeTrie(root);
                exit(1);
            }
            i=0;

            if(c == EOF) break;
        }
        else if(isalpha(c)){
            c = tolower(c);
            str = realloc(str, i+1);
            if(str == NULL){
                freeTrie(root);
                exit(1);
            }
            str[i] = c;
            i++;
        }
    }

    if(argc == 1){
        printTrie(root, str);
    }
    else if(argc == 2 && strcmp(argv[1],"r")==0){
        printTrie_r(root, str);
    }

    free(str);
    freeTrie(root);
    return 0;
}
