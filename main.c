#include <stdio.h>
#include "huffman.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <fichier_a_analyser>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    int freq_table[256] = {0};
    count_frequencies(file, freq_table);

    Node* root = build_huffman_tree(freq_table);
    
    int code[256], top = 0;
    printf("Codes de Huffman generes :\n");
    generate_codes(root, code, top);

    free_tree(root);
    fclose(file);
    return 0;
}