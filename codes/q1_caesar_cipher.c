

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar_cipher(char* text, int key) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            text[i] = (ch - base + key) % 26 + base;
        }
    }
}

int main() {
    char text[100];
    int key;

    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    
    text[strcspn(text, "\n")] = 0;

    printf("Enter the key (1-25): ");
    scanf("%d", &key);

    if (key < 1 || key > 25) {
        printf("Invalid key. Please enter a key between 1 and 25.\n");
        return 1;
    }

    printf("Original message: %s\n", text);
    caesar_cipher(text, key);
    printf("Encrypted message: %s\n", text);

    return 0;
}