
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 5

void generate_matrix(const char* key, char matrix[SIZE][SIZE]);
void prepare_text(const char* text, char* prepared_text);
void playfair_encrypt(const char* prepared_text, char matrix[SIZE][SIZE], char* encrypted_text);
void find_position(char matrix[SIZE][SIZE], char ch, int* row, int* col);

int main() {
    char key[100];
    char text[100];
    char matrix[SIZE][SIZE];
    char prepared_text[200];
    char encrypted_text[200];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    printf("Enter the message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    generate_matrix(key, matrix);
    prepare_text(text, prepared_text);
    playfair_encrypt(prepared_text, matrix, encrypted_text);

    printf("\nPlayfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nOriginal message: %s\n", text);
    printf("Prepared message: %s\n", prepared_text);
    printf("Encrypted message: %s\n", encrypted_text);

    return 0;
}

void generate_matrix(const char* key, char matrix[SIZE][SIZE]) {
    char* temp_key = (char*)malloc(strlen(key) + 26);
    char* alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; 
    int k = 0;
    int* used = (int*)calloc(26, sizeof(int));

    for (int i = 0; i < strlen(key); i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (!used[ch - 'A']) {
            temp_key[k++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (int i = 0; i < strlen(alphabet); i++) {
        char ch = alphabet[i];
        if (!used[ch - 'A']) {
            temp_key[k++] = ch;
        }
    }
    temp_key[k] = '\0';

    k = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = temp_key[k++];
        }
    }

    free(temp_key);
    free(used);
}

void prepare_text(const char* text, char* prepared_text) {
    int k = 0;
    for (int i = 0; i < strlen(text); i++) {
        char ch = toupper(text[i]);
        if (isalpha(ch)) {
            if (ch == 'J') ch = 'I';
            prepared_text[k++] = ch;
        }
    }
    prepared_text[k] = '\0';

    int len = strlen(prepared_text);
    for (int i = 0; i < len; i += 2) {
        if (i + 1 < len && prepared_text[i] == prepared_text[i + 1]) {
            for (int j = len; j > i + 1; j--) {
                prepared_text[j] = prepared_text[j - 1];
            }
            prepared_text[i + 1] = 'X';
            len++;
        }
    }

    if (len % 2 != 0) {
        prepared_text[len] = 'X';
        prepared_text[len + 1] = '\0';
    }
}

void playfair_encrypt(const char* prepared_text, char matrix[SIZE][SIZE], char* encrypted_text) {
    int k = 0;
    for (int i = 0; i < strlen(prepared_text); i += 2) {
        char ch1 = prepared_text[i];
        char ch2 = prepared_text[i + 1];
        int r1, c1, r2, c2;

        find_position(matrix, ch1, &r1, &c1);
        find_position(matrix, ch2, &r2, &c2);

        if (r1 == r2) { // Same row
            encrypted_text[k++] = matrix[r1][(c1 + 1) % SIZE];
            encrypted_text[k++] = matrix[r2][(c2 + 1) % SIZE];
        } else if (c1 == c2) { // Same column
            encrypted_text[k++] = matrix[(r1 + 1) % SIZE][c1];
            encrypted_text[k++] = matrix[(r2 + 1) % SIZE][c2];
        } else { // Rectangle
            encrypted_text[k++] = matrix[r1][c2];
            encrypted_text[k++] = matrix[r2][c1];
        }
    }
    encrypted_text[k] = '\0';
}

void find_position(char matrix[SIZE][SIZE], char ch, int* row, int* col) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}