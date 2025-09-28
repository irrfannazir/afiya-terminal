#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void write_to_header() {
    char buffer[256];
    FILE *file;

    // Open the file for writing (creates it if it doesn't exist)
    file = fopen("include/constant.h", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    printf("Enter API_KEY:\n");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        fprintf(file, "#define API_KEY \"");
        fprintf(file, "%s\"\n", buffer);
    }

    fclose(file);
    printf("API_KEY written successfully.\n");
}

int main() {
    write_to_header();
    return 0;
}
