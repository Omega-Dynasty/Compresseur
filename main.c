#include <stdio.h>
#include <string.h>
#include "huffman.h"

// Fonction pour chercher le code binaire d'un caractère dans l'arbre
void find_and_write_code(Node* root, char c, FILE* out, int* code, int top) {
    if (root->left) {
        code[top] = 0;
        find_and_write_code(root->left, c, out, code, top + 1);
    }
    if (root->right) {
        code[top] = 1;
        find_and_write_code(root->right, c, out, code, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        if (root->character == c) {
            for (int i = 0; i < top; i++) {
                fprintf(out, "%d", code[i]);
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
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // 1. Analyse des fréquences
    int freq_table[256] = {0};
    count_frequencies(file, freq_table);

    // 2. Construction de l'arbre
    Node* root = build_huffman_tree(freq_table);
    
    // 3. Création du fichier compressé .huff
    FILE *out = fopen("test.huff", "w");
    if (out) {
        rewind(file); // On revient au début du fichier source pour le lire à nouveau
        int c;
        int temp_code[256];
        while ((c = fgetc(file)) != EOF) {
            find_and_write_code(root, (char)c, out, temp_code, 0);
        }
        fclose(out);
        printf("Compression terminee : 'test.huff' cree avec succes !\n");
    }

    // Nettoyage
    free_tree(root);
    fclose(file);
    return 0;
}