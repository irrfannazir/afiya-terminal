char* get_message_content(const char* raw_curl_response);
char* create_openrouter_command(const char *prompt, const char* message, const char* result);
char* execute_command(const char* command);
char *clean_the_result(const char *result);