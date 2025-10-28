#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/constant.h"

#define MAX_CMD_LENGTH 2048
#define BASE_URL "https://models.github.ai/inference/chat/completions"
#define CHAT_MODEL "deepseek/DeepSeek-R1-0528"

#ifdef GEMINI

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
    
    return cmd;
}

char* create_simple_command(const char *prompt1) {    
    char* cmd = malloc(MAX_CMD_LENGTH);
    if (cmd == NULL) {
        return NULL;
    }
    snprintf(cmd, MAX_CMD_LENGTH,
        "curl -s -H \"Content-Type: application/json\" "
        "-H \"x-goog-api-key: %s\" "
        "-X POST \"https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent\" "
        "-d \"{ \\\"contents\\\": [ { \\\"parts\\\": [ { \\\"text\\\": \\\"Imagine i am speaking to a girl named %s. Replay like her. %s\\\" } ] } ] }\"",
        HER_NAME, API_KEY, prompt1);
    return cmd;
}

#elif defined(DEEPSEEK)

char* create_openrouter_command(const char *prompt, const char* message, const char* result) {
    if (message == NULL) {
        return NULL;
    }
    
    char* cmd = malloc(MAX_CMD_LENGTH);
    if (cmd == NULL) {
        return NULL;
    }
    snprintf(cmd, MAX_CMD_LENGTH,
        "curl -s -X POST \"https://api.deepseek.com/chat/completions\" "
        "-H \"Content-Type: application/json\" "
        "-H \"Authorization: Bearer %s\" "
        "-d \"{ \\\"model\\\": \\\"deepseek-chat\\\", \\\"messages\\\": [ { \\\"role\\\": \\\"user\\\", \\\"content\\\": \\\"Consider you are a computer to assist the developer for the command they type. Avoid heading and bold letter. %s. The command: %s. The output: %s.\\\" } ], \\\"stream\\\": false }\"",
        API_KEY, prompt, message, result);
    
    return cmd;
}

char* create_simple_command(const char *prompt1) {    
    char* cmd = malloc(MAX_CMD_LENGTH);
    if (cmd == NULL) {
        return NULL;
    }
    snprintf(cmd, MAX_CMD_LENGTH,
        "curl -s -X POST \"https://api.deepseek.com/chat/completions\" "
        "-H \"Content-Type: application/json\" "
        "-H \"Authorization: Bearer %s\" "
        "-d \"{ \\\"model\\\": \\\"deepseek-chat\\\", \\\"messages\\\": [ { \\\"role\\\": \\\"user\\\", \\\"content\\\": \\\"Imagine i am speaking to a girl named %s. Reply like her. %s\\\" } ], \\\"stream\\\": false }\"",
        API_KEY, HER_NAME, prompt1);
    return cmd;
}

#endif

