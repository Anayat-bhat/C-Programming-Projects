#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024
#define MAX_TOKENS 20

// Function Prototypes
void show_help();
void clear_screen();
void add(char **args);
void sub(char **args);
void mul(char **args);
void divide_cmd(char **args);
void write_file(char **args);
void read_file(char **args);
char **parse_input(char *input);
void free_tokens(char **tokens);

// ---------------- MAIN ----------------
int main() {
    char input[MAX_INPUT];
    char **args;

    printf("===== MINI SHELL =====\n");
    printf("Type 'help' to see commands.\n");

    while (1) {
        printf("\nmini-shell> ");
        fgets(input, MAX_INPUT, stdin);

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        // Parse input
        args = parse_input(input);

        if (args[0] == NULL) {
            free_tokens(args);
            continue;
        }

        // Command matching
        if (strcmp(args[0], "help") == 0) {
            show_help();
        } 
        else if (strcmp(args[0], "clear") == 0) {
            clear_screen();
        }
        else if (strcmp(args[0], "exit") == 0) {
            printf("Exiting shell...\n");
            free_tokens(args);
            break;
        }
        else if (strcmp(args[0], "add") == 0) {
            add(args);
        }
        else if (strcmp(args[0], "sub") == 0) {
            sub(args);
        }
        else if (strcmp(args[0], "mul") == 0) {
            mul(args);
        }
        else if (strcmp(args[0], "div") == 0) {
            divide_cmd(args);
        }
        else if (strcmp(args[0], "write") == 0) {
            write_file(args);
        }
        else if (strcmp(args[0], "read") == 0) {
            read_file(args);
        }
        else {
            printf("Unknown command. Type 'help'.\n");
        }

        free_tokens(args);
    }

    return 0;
}

// ---------------- COMMAND FUNCTIONS ----------------

void show_help() {
    printf("\nAvailable Commands:\n");
    printf("help                  - Show commands\n");
    printf("clear                 - Clear screen\n");
    printf("exit                  - Exit shell\n");
    printf("add a b               - Add numbers\n");
    printf("sub a b               - Subtract numbers\n");
    printf("mul a b               - Multiply numbers\n");
    printf("div a b               - Divide numbers\n");
    printf("write file text       - Write text to file\n");
    printf("read file             - Read file content\n");
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void add(char **args) {
    if (args[1] && args[2]) {
        int a = atoi(args[1]);
        int b = atoi(args[2]);
        printf("Result: %d\n", a + b);
    } else {
        printf("Usage: add a b\n");
    }
}

void sub(char **args) {
    if (args[1] && args[2]) {
        int a = atoi(args[1]);
        int b = atoi(args[2]);
        printf("Result: %d\n", a - b);
    } else {
        printf("Usage: sub a b\n");
    }
}

void mul(char **args) {
    if (args[1] && args[2]) {
        int a = atoi(args[1]);
        int b = atoi(args[2]);
        printf("Result: %d\n", a * b);
    } else {
        printf("Usage: mul a b\n");
    }
}

void divide_cmd(char **args) {
    if (args[1] && args[2]) {
        int a = atoi(args[1]);
        int b = atoi(args[2]);

        if (b == 0) {
            printf("Error: Division by zero\n");
            return;
        }

        printf("Result: %.2f\n", (float)a / b);
    } else {
        printf("Usage: div a b\n");
    }
}

void write_file(char **args) {
    if (args[1] && args[2]) {
        FILE *fp = fopen(args[1], "w");
        if (!fp) {
            printf("Error opening file\n");
            return;
        }

        // Write all text arguments
        for (int i = 2; args[i] != NULL; i++) {
            fprintf(fp, "%s", args[i]);

            // Add space between words
            if (args[i + 1] != NULL) {
                fprintf(fp, " ");
            }
        }

        fclose(fp);

        printf("Written to %s successfully.\n", args[1]);
    } else {
        printf("Usage: write filename text\n");
    }
}

void read_file(char **args) {
    if (args[1]) {
        FILE *fp = fopen(args[1], "r");
        if (!fp) {
            printf("File not found\n");
            return;
        }

        char ch;
        while ((ch = fgetc(fp)) != EOF) {
            putchar(ch);
        }

        fclose(fp);
    } else {
        printf("Usage: read filename\n");
    }
}

// ---------------- INPUT PARSING ----------------

char **parse_input(char *input) {
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    char *token;
    int i = 0;

    token = strtok(input, " ");

    while (token != NULL && i < MAX_TOKENS - 1) {
        tokens[i] = malloc(strlen(token) + 1);
        strcpy(tokens[i], token);
        i++;
        token = strtok(NULL, " ");
    }

    tokens[i] = NULL;
    return tokens;
}

void free_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}