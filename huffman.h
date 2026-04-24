#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>

// Définition de la structure
typedef struct Node {
    char character;
    int frequency;
    struct Node *left, *right;
} Node;

// Déclarations des fonctions pour que main.c les connaisse
void count_frequencies(FILE *file, int *freq_table);
Node* create_node(char c, int freq);
Node* build_huffman_tree(int *freq_table);
void generate_codes(Node* root, int* code, int top);
void free_tree(Node* root);

#endif