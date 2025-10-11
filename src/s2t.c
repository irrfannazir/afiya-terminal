#include <stdlib.h>
#include <string.h>

char *convert_to_text(const char *str) {
    if (!str) return NULL;

    // Allocate memory for the output string (max same length as input)
    char *result = (char *)malloc(strlen(str) + 1);
    if (!result) return NULL;

    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] == '\\') {  // found an escape character
            i++;
            switch (str[i]) {
                case 'n': result[j++] = '\n'; break;
                case 't': result[j++] = '\t'; break;
                case '\\': result[j++] = '\\'; break;
                case '"': result[j++] = '"'; break;
                case 'r': result[j++] = '\r'; break;
                case '0': result[j++] = '\0'; break;
                default:
                    // If unknown escape, just copy literally
                    result[j++] = '\\';
                    result[j++] = str[i];
                    break;
            }
        } else {
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';
    return result;
}