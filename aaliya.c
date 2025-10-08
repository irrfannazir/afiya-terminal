#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/get.h"
#define HER_NAME "aliya"

// #define DEBUG_MODE
// #define RESULT_DEBUG_MODE

int main() {
    char command[256];
    int isdone = 0;
    while (1) {
        printf("%s-terminal> ", HER_NAME);
        if (fgets(command, sizeof(command), stdin) == NULL) break;
        
        // remove newline
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "lets breakup") == 0) break;

        // system(command); // runs command in real shell
        char *result = execute_command(command);
        printf("%s\n", result);

        //Help Desk
        if(strcmp(command, "") == 0 || strcmp(result, "") == 0){
            continue;
        }
        char *msg_cmd = create_openrouter_command("Just say \"No\" if the command wrote is wrong. If i wrote the right program say \"Yes\"", command, clean_the_result(result));
        char *deepseek_return = execute_command(msg_cmd);
        if(strcmp(deepseek_return, "{\"error\":{\"message\":\"Internal Server Error\",\"code\":500}}") == 0){
            printf("%s> Check the Internet connection.\n", HER_NAME);
            continue;
        }
        char *deepseek_result = get_message_content(deepseek_return);
        #ifdef DEBUG_MODE
            printf("Command prompted.\n>> %s \n\n", msg_cmd);
            printf("Result >> %s \n\n", deepseek_return);
            printf("Content >> %s \n\n", deepseek_result);
        #endif
        if(deepseek_result == NULL){
            printf("Unknown error.\n>> %s \n\n", deepseek_return);
        }else if(strcmp(deepseek_result, "No") == 0){
            msg_cmd = create_openrouter_command("Just explain what error i made briefly", command, clean_the_result(result));
            deepseek_return = execute_command(msg_cmd);
            deepseek_result = get_message_content(deepseek_return);
            #ifdef RESULT_DEBUG_MODE
                printf("Command prompted.\n>> %s \n\n", msg_cmd);
                printf("Result >> %s \n\n", deepseek_return);
                printf("Content >> %s \n\n", deepseek_result);
            #endif
            if(deepseek_result == NULL){
                printf("%s> Sorry dear. i am busy now. please ask me later\n", HER_NAME);
                continue;
            }
            printf("%s> %s\n\n", HER_NAME, deepseek_result);
            isdone = 1;
        }else if(strcmp(deepseek_result, "Yes") == 0 && isdone){
            printf("%s> You have done it right.\n", HER_NAME);
            isdone = 0;
        }else{
            printf("%s> You got some error with Gemini\n", HER_NAME);
        }
    }
    return 0;
}
