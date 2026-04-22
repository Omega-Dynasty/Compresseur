#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char character;
    int frequency;
    struct Node *left, *right;
} Node;

void count_frequencies(FILE *file, int *freq_table);