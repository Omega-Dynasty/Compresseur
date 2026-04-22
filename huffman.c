#include "huffman.h"

void count_frequencies(FILE *file, int *freq_table) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        freq_table[(unsigned char)c]++;
    }
}