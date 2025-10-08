#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/constant.h"

#define MAX_CMD_LENGTH 2048
#define BASE_URL "https://models.github.ai/inference/chat/completions"
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
        "curl -s -H \"Content-Type: application/json\" "
        "-H \"x-goog-api-key: %s\" "
        "-X POST \"https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent\" "
        "-d \"{ \\\"contents\\\": [ { \\\"parts\\\": [ { \\\"text\\\": \\\"Consider you are a computer to assist the developer for the command they type. Avoid heading and bold letter. %s. The command: %s. The output: %s.\\\" } ] } ] }\"",
        API_KEY, prompt, message, result);
    
    // snprintf(cmd, MAX_CMD_LENGTH,
    //     "curl -s -X POST \"http://168.231.121.107:8080/generate\" "
    //     "-H \"Content-Type: application/json\" "
    //     "-d \"{ \\\"prompt\\\": \\\"Consider you are a computer to assist me for the command i type. Avoid heading and bold letter. Try to say something less than 50 words. %s. The command: %s. The output: `%s` \\\", \\\"max_tokens\\\": 500 }\"",
    //     prompt, message, result);
    // printf("cmd >>%s", cmd);
    return cmd;
}
