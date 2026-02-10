
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SYMBOLS 256

typedef struct {
    char symbol;
    int count;
} SymbolFreq;

int compare_freq(const void* a, const void* b) {
    return ((SymbolFreq*)b)->count - ((SymbolFreq*)a)->count;
}

void frequency_analysis(const char* text) {
    SymbolFreq frequencies[MAX_SYMBOLS] = {0};
    int freq_count = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        int found = 0;
        for (int j = 0; j < freq_count; j++) {
            if (frequencies[j].symbol == ch) {
                frequencies[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            frequencies[freq_count].symbol = ch;
            frequencies[freq_count].count = 1;
            freq_count++;
        }
    }

    qsort(frequencies, freq_count, sizeof(SymbolFreq), compare_freq);

    printf("Frequency analysis:\n");
    for (int i = 0; i < freq_count; i++) {
        printf("'%c': %d\n", frequencies[i].symbol, frequencies[i].count);
    }
}

void decrypt_with_mapping(const char* text, const char* mapping_from, const char* mapping_to) {
    char decrypted_text[1000];
    strcpy(decrypted_text, text);

    for (int i = 0; decrypted_text[i] != '\0'; i++) {
        for (int j = 0; mapping_from[j] != '\0'; j++) {
            if (decrypted_text[i] == mapping_from[j]) {
                decrypted_text[i] = mapping_to[j];
                break;
            }
        }
    }
    printf("Decrypted text: %s\n", decrypted_text);
}


int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";

    printf("Ciphertext: %s\n\n", ciphertext);

    frequency_analysis(ciphertext);

    printf("\nBased on the frequency analysis, you can try to map characters.\n");
    printf("For example, the most frequent characters could be 'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'u'.\n\n");

    char mapping_from[100];
    char mapping_to[100];
    int mapping_count = 0;

    while (1) {
        printf("Enter a character from the ciphertext to map (or 'q' to quit): ");
        char from;
        scanf(" %c", &from);
        if (from == 'q') {
            break;
        }

        printf("Enter the character to map it to: ");
        char to;
        scanf(" %c", &to);

        mapping_from[mapping_count] = from;
        mapping_to[mapping_count] = to;
        mapping_count++;
        mapping_from[mapping_count] = '\0';
        mapping_to[mapping_count] = '\0';

        decrypt_with_mapping(ciphertext, mapping_from, mapping_to);
    }

    return 0;
}
