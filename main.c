#include <stdio.h>
#include <string.h>
#include "huffman.h"

// Fonction pour récupérer le code d'un caractère spécifique
void get_code(Node* root, char c, int* code, int top, char* result) {
    if (root->left) {
        code[top] = 0;
        get_code(root->left, c, code, top + 1, result);
    }
    if (root->right) {
        code[top] = 1;
        get_code(root->right, c, code, top + 1, result);
    }
    if (!(root->left) && !(root->right)) {
        if (root->character == c) {
            for (int i = 0; i < top; i++) {
                sprintf(result + strlen(result), "%d", code[i]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <fichier_a_analyser>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erreur ouverture");
        return 1;
    }

    int freq_table[256] = {0};
    count_frequencies(file, freq_table);

    Node* root = build_huffman_tree(freq_table);
    
    // Création du fichier compressé .ash
    FILE *out = fopen("test.ash", "w");
    if (out) {
        rewind(file); // On repart au début du fichier source
        int c;
        int temp_code[256];
        while ((c = fgetc(file)) != EOF) {
            char bit_string[256] = "";
            get_code(root, (char)c, temp_code, 0, bit_string);
            fprintf(out, "%s", bit_string);
        }
        fclose(out);
        printf("Fichier 'test.ash' genere avec succes !\n");
    }

    free_tree(root);
    fclose(file);
    return 0;
}