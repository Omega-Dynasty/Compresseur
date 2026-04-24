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

Node* build_huffman_tree(int *freq_table) {
    Node *nodes[256];
    int size = 0;

    for (int i = 0; i < 256; i++) {
        if (freq_table[i] > 0) {
            nodes[size++] = create_node((char)i, freq_table[i]);
        }
    }

    while (size > 1) {
        // Tri simple pour trouver les deux plus petits
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (nodes[i]->frequency > nodes[j]->frequency) {
                    Node *temp = nodes[i];
                    nodes[i] = nodes[j];
                    nodes[j] = temp;
                }
            }
        }

        Node *left = nodes[0];
        Node *right = nodes[1];
        
        Node *parent = create_node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        nodes[0] = parent;
        for (int i = 1; i < size - 1; i++) {
            nodes[i] = nodes[i + 1];
        }
        size--;
    }
    return nodes[0];
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