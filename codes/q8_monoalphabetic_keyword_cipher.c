
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void generate_keyword_cipher(const char* keyword, char* cipher_alphabet) {
    char* temp_key = (char*)malloc(strlen(keyword) + 26);
    char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int k = 0;
    int* used = (int*)calloc(26, sizeof(int));

    for (int i = 0; i < strlen(keyword); i++) {
        char ch = toupper(keyword[i]);
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
    strcpy(cipher_alphabet, temp_key);

    free(temp_key);
    free(used);
}

void encrypt_with_keyword_cipher(char* text, const char* cipher_alphabet) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            int index = ch - base;
            char replacement = cipher_alphabet[index];
            text[i] = islower(ch) ? tolower(replacement) : toupper(replacement);
        }
    }
}

int main() {
    char keyword[100];
    char text[100];
    char cipher_alphabet[27];

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    printf("Enter the message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    generate_keyword_cipher(keyword, cipher_alphabet);

    printf("\nCipher alphabet: %s\n", cipher_alphabet);
    printf("Original message: %s\n", text);
    encrypt_with_keyword_cipher(text, cipher_alphabet);
    printf("Encrypted message: %s\n", text);

    return 0;
}
