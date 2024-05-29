#include <stdio.h>
#include <string.h>

// Function prototype for get_string
char* get_string(char prompt[], char str[], int size);

int main(void) {
    char name[100];
    char favoriteColor[100];

    get_string("What is your name? ", name, sizeof(name)); // Custom prompt for name
    printf("Hello, %s\n", name);

    get_string("What is your favorite color? ", favoriteColor, sizeof(favoriteColor)); // Custom prompt for favorite color
    printf("%s, that's a nice color!\n", favoriteColor);

    return 0;
}

// Function to get a string from the user with a custom prompt
char* get_string(char prompt[], char str[], int size) {
    printf("%s", prompt);
    if (fgets(str, size, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(str);
        if (len > 0 && str[len-1] == '\n') {
            str[len-1] = '\0';
        }
    }
    return str;
}
