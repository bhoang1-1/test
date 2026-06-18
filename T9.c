#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t9_lib.h"

#include "t9_lib.h"

typedef struct T9 {
  struct T9 *children[11];
  char *word;
} T9;

T9* InitializeEmptyT9() {
    T9* node = malloc(sizeof(T9));
    if (node == NULL) {
        fprintf(stderr, "malloc failed\n");
        return NULL;
    }
    for (int i = 0; i < 11; i++) {
        node->children[i] = NULL;
    }
    node->word = NULL;
    return node;
}

T9* InitializeFromFileT9(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    T9* trie = InitializeEmptyT9();
    if (trie == NULL){
        fclose(file);
        return NULL;
    }

    char buffer[52];

    while(fgets(buffer, 52, file) != NULL){  // 52 to account for \n and \0
        buffer[strcspn(buffer, "\n")] = '\0'; // find the newline, \n, and replaces it with the termination \0
        AddWordToT9(trie, buffer);
    }

    fclose(file);
    return trie;
}

static int charToDigit(char c) {
    char* keys[] = {"abc", "def", "ghi", "jkl",
                    "mno", "pqrs", "tuv", "wxyz"};
    for (int i = 0; i < 8; i++) {
        if (strchr(keys[i], c) != NULL) {  // search string for char c, if no null return corresponding digit
            return i + 2;
        }
    }
    return -1;
}


void AddWordToT9(T9* dict, const char* word) {
    if (word == NULL || word[0] == '\0') return; // "\0" just checks if word == ""

    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] < 'a' || word[i] > 'z') return; // checks if given word is all lower case or not
    }

    // TRAVERSE TRIE
    T9* curr = dict;
    for (int i = 0; word[i] != '\0'; i++) {
        
        int digit = charToDigit(word[i]);
        if (digit < 2 || digit > 9) return;
        
        if(curr->children[digit] == NULL){
            curr->children[digit] = InitializeEmptyT9();
            if (curr->children[digit] == NULL) return;  // malloc check
        }
        curr = curr->children[digit];
    }

    while(curr->word != NULL){

        if (strncmp(curr->word, word, strlen(word) + 1) == 0) return; // string compare, check if word is a duplicate, if duplicate return
        
        if(curr->children[10] == NULL){
            curr->children[10] = InitializeEmptyT9();
            if (curr->children[10] == NULL) return; // malloc check
        }
        curr = curr->children[10];
    }

    curr->word = malloc(strlen(word) + 1); // create own chunk of memory for word
    if (curr->word == NULL) {
        fprintf(stderr, "malloc failed\n");
        return;
    }
    strncpy(curr->word, word, strlen(word) + 1); // copy word into node
}

char* PredictT9(T9* dict, const char* nums) {
    // TODO: your code goes here
    return NULL;  // you will want to change this
}

void DestroyT9(T9* dict) {
    // TODO: your code goes here
}
