
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 5

void generate_matrix(const char* key, char matrix[SIZE][SIZE]);
void playfair_decrypt(const char* text, char matrix[SIZE][SIZE], char* decrypted_text);
void find_position(char matrix[SIZE][SIZE], char ch, int* row, int* col);

int main() {
    char keyword[] = "PLAYFAIR EXAMPLE";
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char matrix[SIZE][SIZE];
    char decrypted_text[200];

    generate_matrix(keyword, matrix);
    playfair_decrypt(ciphertext, matrix, decrypted_text);

    printf("Keyword: %s\n", keyword);
    printf("\nPlayfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nCiphertext: %s\n", ciphertext);
    printf("Decrypted message: %s\n", decrypted_text);

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
        if (isalpha(ch) && !used[ch - 'A']) {
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

void playfair_decrypt(const char* text, char matrix[SIZE][SIZE], char* decrypted_text) {
    int k = 0;
    for (int i = 0; i < strlen(text); i += 2) {
        char ch1 = text[i];
        char ch2 = text[i + 1];
        int r1, c1, r2, c2;

        find_position(matrix, ch1, &r1, &c1);
        find_position(matrix, ch2, &r2, &c2);

        if (r1 == r2) { // Same row
            decrypted_text[k++] = matrix[r1][(c1 - 1 + SIZE) % SIZE];
            decrypted_text[k++] = matrix[r2][(c2 - 1 + SIZE) % SIZE];
        } else if (c1 == c2) { // Same column
            decrypted_text[k++] = matrix[(r1 - 1 + SIZE) % SIZE][c1];
            decrypted_text[k++] = matrix[(r2 - 1 + SIZE) % SIZE][c2];
        } else { // Rectangle
            decrypted_text[k++] = matrix[r1][c2];
            decrypted_text[k++] = matrix[r2][c1];
        }
    }
    decrypted_text[k] = '\0';
}
