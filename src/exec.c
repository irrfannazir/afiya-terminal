#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* execute_command(char* command) {
    FILE *fp;
    char buffer[128];
    char *result = malloc(1);
    result[0] = '\0';
    size_t total_size = 0;
    
    // Open the command for reading
    #if defined(_WIN32) || defined(_WIN64)
    strcat(command, " 2>&1");
    fp = _popen(command, "r");
    #elif defined(__linux__)
    strcat(command, " | wc -w");
    fp = popen(command, "r");
    #else
    printf("Operating System: Unknown\n");
    #endif
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
    #if defined(_WIN32) || defined(_WIN64)
    int status = _pclose(fp);
    #elif defined(__linux__)
    int status = pclose(fp);
    #else
    printf("Operating System: Unknown\n");
    #endif
    if (status == -1) {
        printf("Error: Failed to close command\n");
        free(result);
        return NULL;
    }
    return result;
}