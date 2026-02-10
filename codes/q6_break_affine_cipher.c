
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void affine_decrypt(char* text, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("Error: Modular inverse does not exist for the given 'a'.\n");
        return;
    }

    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            int c = ch - base;
            int p = (a_inv * (c - b + 26)) % 26;
            text[i] = p + base;
        }
    }
}

int main() {
    char text[100];
    int a = 3;
    int b = 15;

    printf("Enter a message to decrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Encrypted message: %s\n", text);
    affine_decrypt(text, a, b);
    printf("Decrypted message: %s\n", text);

    return 0;
}
