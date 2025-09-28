#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LENGTH 2048
#define BASE_URL "https://models.github.ai/inference/chat/completions"
#define API_KEY "AIzaSyCHPqqtPZWdc6PrWTn66-G9V4FzYR_FROk"
#define CHAT_MODEL "deepseek/DeepSeek-R1-0528"

char* create_openrouter_command(const char *prompt, const char* message, const char* result) {
    if (message == NULL) {
        return NULL;
    }
    
    char* cmd = malloc(MAX_CMD_LENGTH);
    if (cmd == NULL) {
        return NULL;
    }

    snprintf(cmd, MAX_CMD_LENGTH,
        "curl -H \"Content-Type: application/json\" "
        "-H \"x-goog-api-key: %s\" "
        "-X POST \"https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent\" "
        "-d \"{ \\\"contents\\\": [ { \\\"parts\\\": [ { \\\"text\\\": \\\"Consider you are a computer to assist the developer for the command they type. Avoid heading and bold letter. %s. The command: %s. The output: %s.\\\" } ] } ] }\"",
        API_KEY, prompt, message, result);
    return cmd;
}
