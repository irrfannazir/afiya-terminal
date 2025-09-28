#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *clean_the_result(const char *result) {
    if (result == NULL) {
        return NULL;
    }
    
    // First pass: calculate the required length
    size_t len = 2; // Start with 2 for the opening and closing quotes
    for (const char *p = result; *p; p++) {
        switch (*p) {
            case '"':
            case '\\':
                len += 2; // Need to escape: \" or \\
                break;
            case '\n':
                len += 2; // \n becomes \\n
                break;
            case '\t':
                len += 2; // \t becomes \\t
                break;
            case '\r':
                len += 2; // \r becomes \\r
                break;
            default:
                len += 1;
                break;
        }
    }
    
    // Allocate memory for the cleaned string
    char *cleaned = malloc(len + 1); // +1 for null terminator
    if (cleaned == NULL) {
        return NULL;
    }
    
    // Second pass: build the escaped string
    char *dest = cleaned;
    *dest++ = '`'; // Opening quote
    
    for (const char *p = result; *p; p++) {
        switch (*p) {
            case '"':
                *dest++ = '\\';
                *dest++ = '"';
                break;
            case '\\':
                *dest++ = '\\';
                *dest++ = '\\';
                break;
            case '\n':
                *dest++ = '\\';
                *dest++ = 'n';
                break;
            case '\t':
                *dest++ = '\\';
                *dest++ = 't';
                break;
            case '\r':
                *dest++ = '\\';
                *dest++ = 'r';
                break;
            default:
                *dest++ = *p;
                break;
        }
    }
    
    *dest++ = '`'; // Closing quote
    *dest = '\0'; // Null terminator
    
    return cleaned;
}