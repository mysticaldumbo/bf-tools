#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 30000

char memory[MEMORY_SIZE] = {0};
char *ptr = memory;

void run_brainfuck(char *code) {
    while (*code) {
        switch (*code) {
            case '>':
                ++ptr;
                break;
            case '<':
                --ptr;
                break;
            case '+':
                ++(*ptr);
                break;
            case '-':
                --(*ptr);
                break;
            case '[':
                if (!(*ptr)) {
                    int loop = 1;
                    while (loop > 0) {
                        ++code;
                        if (*code == '[')
                            ++loop;
                        else if (*code == ']')
                            --loop;
                    }
                }
                break;
            case ']':
                if (*ptr) {
                    int loop = 1;
                    while (loop > 0) {
                        --code;
                        if (*code == '[')
                            --loop;
                        else if (*code == ']')
                            ++loop;
                    }
                }
                break;
            case '.':
                putchar(*ptr);
                break;
            case ',':
                *ptr = getchar();
                break;
            default:
                break;
        }
        ++code;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s <brainfuck_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("error opening file.");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *code = new char[length + 1];
    if (!code) {
        perror("error allocating memory.");
        fclose(file);
        return 1;
    }

    fread(code, 1, length, file);
    fclose(file);
    code[length] = '\0';

    run_brainfuck(code);

    free(code);

    printf("\nPress Enter to exit...");
    while (getchar() != '\n');

    return 0;
}