#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "include/shell.h"


void handle_sigint(int sig) {
    if (remove(NULL_FILE)){
        perror("Remove wehaveone.ss manually");
    }
}

int main(){
    if(fopen(NULL_FILE, "r")){
        printf("There is one running.\n");
        return 1;
    }
    signal(SIGINT, handle_sigint);
    int result = system("terminal");
    if (result){
        perror("terminal.exe not found");
    }
    return 0;
}
