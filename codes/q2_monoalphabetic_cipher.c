
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void monoalphabetic_cipher(char* text, const char* key) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            int index = ch - base;
            char replacement = key[index];
            text[i] = islower(ch) ? tolower(replacement) : toupper(replacement);
        }
    }
}

int main() {
    char text[100];
    char key[27];

    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Enter the substitution key (26 unique letters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    if (strlen(key) != 26) {
        printf("Invalid key. Please enter a key with 26 unique letters.\n");
        return 1;
    }

    printf("Original message: %s\n", text);
    monoalphabetic_cipher(text, key);
    printf("Encrypted message: %s\n", text);

    return 0;
}