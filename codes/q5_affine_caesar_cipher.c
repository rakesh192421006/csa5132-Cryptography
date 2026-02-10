
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void affine_cipher(char* text, int a, int b) {
    if (gcd(a, 26) != 1) {
        printf("Error: 'a' is not coprime with 26. The cipher is not one-to-one.\n");
        return;
    }

    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            text[i] = (((a * (ch - base)) + b) % 26) + base;
        }
    }
}

int main() {
    char text[100];
    int a, b;

    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Enter the value of 'a' (must be coprime with 26): ");
    scanf("%d", &a);

    printf("Enter the value of 'b': ");
    scanf("%d", &b);

    if (gcd(a, 26) != 1) {
        printf("Invalid value for 'a'. 'a' must be coprime with 26.\n");
        return 1;
    }

    printf("Original message: %s\n", text);
    affine_cipher(text, a, b);
    printf("Encrypted message: %s\n", text);

    return 0;
}
