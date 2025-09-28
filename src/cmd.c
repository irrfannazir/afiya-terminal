#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* execute_command(const char* command) {
    FILE *fp;
    char buffer[128];
    char *result = malloc(1);
    result[0] = '\0';
    size_t total_size = 0;
    
    // Open the command for reading
    fp = _popen(command, "r");
    if (fp == NULL) {
        printf("Error: Failed to run command\n");
        free(result);
        return NULL;
    }
    
    // Read the output
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        result = realloc(result, total_size + chunk_size + 1);
        strcpy(result + total_size, buffer);
        total_size += chunk_size;
    }
    
    // Close and check for errors
    int status = _pclose(fp);
    if (status == -1) {
        printf("Error: Failed to close command\n");
        free(result);
        return NULL;
    }
    return result;
}