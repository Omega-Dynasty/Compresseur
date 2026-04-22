#include "huffman.h"

void count_frequencies(FILE *file, int *freq_table) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        freq_table[(unsigned char)c]++;
    }
}

Node* create_node(char c, int freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->character = c;
    node->frequency = freq;
    node->left = node->right = NULL;
    return node;
}

// Note : Dans un vrai projet, on utiliserait un Min-Heap ici.
Node* build_huffman_tree(int *freq_table) {
    // 1. Créer des nœuds feuilles pour chaque caractère présent
    // 2. Tant qu'il reste > 1 nœud, fusionner les deux plus petits
    // 3. Retourner la racine
    return NULL; // Implémentation simplifiée pour l'exemple
}

void generate_codes(Node* root, int* code, int top) {
    if (root->left) {
        code[top] = 0;
        generate_codes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = 1;
        generate_codes(root->right, code, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) printf("%d", code[i]);
        printf("\n");
    }
}

void free_tree(Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}