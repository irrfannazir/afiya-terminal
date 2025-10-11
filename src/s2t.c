
void convert_to_text(char *str) {
    char *src = str, *dst = str;

    while (*src) {
        if (*src == '\\') { // Found a backslash
            src++;
            switch (*src) {
                case 'n':  *dst = '\n'; break;
                case 't':  *dst = '\t'; break;
                case 'r':  *dst = '\r'; break;
                case '\\': *dst = '\\'; break;
                case '\"': *dst = '\"'; break;
                case '\'': *dst = '\''; break;
                case '0':  *dst = '\0'; break;
                case 'b':  *dst = '\b'; break;
                case 'f':  *dst = '\f'; break;
                case 'v':  *dst = '\v'; break;
                default:
                    // Unrecognized escape — keep both characters
                    *dst++ = '\\';
                    *dst = *src;
                    break;
            }
        } else {
            *dst = *src;
        }

        if (*src) src++;
        dst++;
    }

    *dst = '\0'; 
}