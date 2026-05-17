#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* vigenere_encrypt(char text[], char key[]) {
    int text_length = strlen(text);
    int key_length = strlen(key);
    char* return_string = malloc(text_length);
    strncpy(return_string, text, text_length);
    for (int i = 0; i < text_length; ++i) {
        int key_index = i % key_length;
        int offset = key[key_index] - 'a';
        if (return_string[i] >= 'a' && return_string[i] <= 'z') {
            return_string[i] = 'a' + (return_string[i] - 'a' + offset) % 26;
        } else if (return_string[i] >= 'A' && return_string[i] <= 'Z') {
            return_string[i] = 'A' + (return_string[i] - 'A' + offset) % 26;
        }
    }
    return return_string;
}

char* caesar_encrypt(char text[], int shift) {
    int length = strlen(text);
    char* return_string = malloc(length);
    strncpy(return_string, text, length);
    for (int i = 0; i < length; ++i) {
        if (return_string[i] >= 'a' && return_string[i] <= 'z') {
            return_string[i] = 'a' + (return_string[i] - 'a' + shift) % 26;
        } else if (return_string[i] >= 'A' && return_string[i] <= 'Z') {
            return_string[i] = 'A' + (return_string[i] - 'A' + shift) % 26;
        }
    }
    return return_string;
}

int main(int argc, char *argv[]) {
    if(argc < 3)
    {
        printf("Usage: encrypt <text> <key>\n");
        return 1;
    }

    int shift = 0;
    sscanf(argv[2], "%d", &shift);
    printf("Encrypted text: %s\n", caesar_encrypt(argv[1], shift));

    return 0;
}
