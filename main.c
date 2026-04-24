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
    
    printf("Analyse terminee pour : %s\n", argv[1]);
    fclose(file);
    return 0;
}