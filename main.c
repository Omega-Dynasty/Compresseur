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
    count_frequencies(file, freq_table); // Fonction de ta branche feat-analyse
    
    // ... après count_frequencies(file, freq_table);

    printf("Resultats de l'analyse :\n");
    for (int i = 0; i < 256; i++) {
        if (freq_table[i] > 0) {
            printf("Caractere '%c' (code %d) : %d fois\n", i, i, freq_table[i]);
        }
    }
}