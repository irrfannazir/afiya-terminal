#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "include/get.h"
#include "include/shell.h"
#include "include/constant.h"


int main() {
    char command[256];
    int afiya = 0;
    int isdone = 0;
    while (1) {
        printf("%s-terminal> ", HER_NAME);
        if (fgets(command, sizeof(command), stdin) == NULL) break;
        
        // remove newline
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "bye") == 0) {
            break;
        }
        if (strcmp(command, "afiya") == 0){
            char prompt[256];
            do{
                puts("You > ");
                fflush(stdout);
                if (!fgets(prompt, sizeof(prompt), stdin)) break;
                prompt[strcspn(prompt, "\n")] = 0;
                if (strcmp(prompt, "see you") == 0) break;
                char *afiya_response = ask_her(prompt);
                if (afiya_response != NULL) printf("%s> %s\n", HER_NAME, afiya_response);
                free(afiya_response);
            }while(1);
            continue;
        }

        // system(command); // runs command in real shell
        char *result = execute_command(command);
        printf("%s\n", result);
        
        //Help Desk
        if(strcmp(command, "") == 0 || strcmp(result, "") == 0){
            continue;
        }
        char *deepseek_result = ask_model("Just say \"No\" if the command wrote is wrong. If i wrote the right program say \"Yes\"", command, clean_the_result(result));
        if(deepseek_result == NULL){
            continue;
        }else if(strcmp(deepseek_result, "No") == 0){
            deepseek_result = ask_model("Just explain what error i made briefly and give the right command to run", command, clean_the_result(result));
            printf("%s> %s\n\n", HER_NAME, deepseek_result);
            isdone = 1;
        }else if(strcmp(deepseek_result, "Yes") == 0){
            if(isdone){
                printf("%s> You have done it right.\n", HER_NAME);
                isdone = 0;
            }
        }else{
            printf("%s> I am not able to assist with the model. The respone of the model: %s\n", HER_NAME, deepseek_result);
        }
    }
    return 0;
}
