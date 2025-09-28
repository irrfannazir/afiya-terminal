#include <stdio.h>
#include <string.h>

// Extracts the first "text" value from a JSON string
const char* get_message_content(const char *json) {
    static char buffer[256];  // holds extracted value
    const char *key = "\"text\":";
    const char *pos = strstr(json, key);
    
    if (!pos) {
        return NULL; // "text" not found
    }
    
    // Find the first quote after "text":
    pos = strchr(pos + strlen(key), '\"');  
    if (!pos) return NULL;
    pos++;  // move past opening quote of value
    
    char *escape = strchr(pos, '\\');
    char *end = strchr(pos, '\"');
    while(escape == end - 1){
        end = strchr(pos, '\"');
        if (!end) return NULL;
    }

    size_t len = end - pos;
    if (len >= sizeof(buffer)) len = sizeof(buffer) - 1;

    strncpy(buffer, pos, len);
    buffer[len] = '\0';

    return buffer;
}