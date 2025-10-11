#include <stdlib.h>

char* get_message_content(const char* raw_curl_response);
char* create_openrouter_command(const char *prompt, const char* message, const char* result);
char* create_simple_command(const char *prompt1);
char* execute_command(const char* command);
char *clean_the_result(const char *result);
char *convert_to_text(char *str);


static inline int check_the_internet(){
    int status = system(
        "curl -s --connect-timeout 5 google.com > temp.txt"
    );
    remove("temp.txt");
    return status;
} 

static inline char *ask_model(char *prompt, char *command, char *result){
    char *msg_cmd = create_openrouter_command(prompt, command, clean_the_result(result));
    char *deepseek_response = execute_command(msg_cmd);
    if(check_the_internet()){
        printf("Check The Internet.\n");
        return NULL;
    }
    char *deepseek_result = get_message_content(deepseek_response);
    if(deepseek_result == NULL){
        printf("Unknown error.\n>> %s \n\n", deepseek_response);
    }
    convert_to_text(deepseek_result);
    return deepseek_result;
}

static inline char *ask_her(char *prompt){
    char *msg_cmd = create_simple_command(prompt);
    char *deepseek_response = execute_command(msg_cmd);
    if(check_the_internet()){
        printf("Check The Internet.\n");
        return NULL;
    }
    char *deepseek_result = get_message_content(deepseek_response);
    if(deepseek_result == NULL){
        printf("Unknown error.\n>> %s \n\n", deepseek_response);
    }
    free(msg_cmd);
    free(deepseek_response);
    deepseek_result = convert_to_text(deepseek_result);
    return deepseek_result;
}