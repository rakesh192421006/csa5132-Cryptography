
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenere_cipher(char* text, const char* key) {
    int key_len = strlen(key);
    int key_index = 0;
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            char key_char = toupper(key[key_index % key_len]);
            int shift = key_char - 'A';
            text[i] = (ch - base + shift) % 26 + base;
            key_index++;
        }
    }
}

int main() {
    char text[100];
    char key[100];

    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    printf("Original message: %s\n", text);
    vigenere_cipher(text, key);
    printf("Encrypted message: %s\n", text);

    return 0;
}