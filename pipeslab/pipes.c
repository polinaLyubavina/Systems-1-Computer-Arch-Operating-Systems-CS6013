#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int fd1[2];                                                          //stores two ends of the first pipe
    int fd2[2];                                                          //stores two ends of the second pipe
    char input_str[100];
    char cmdinput = argv[1];
    pid_t rc = fork();                                                   //creates fork

    if(pipe(fd1) == -1 || pipe(fd2) == -1) {                             //pipe failed, exit
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    if(rc < 0) {                                                         //fork failed, exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    else if(rc > 0) {                                                   //get parent
        printf("I am parent (pid:%d)\n", (int) getpid());

        close(fd1[0]);                                                          // Write input string and close writing end of both pipes
        write(fd1[1], input_str, strlen(input_str) + 1);
        close(fd1[1]);
        close(fd2[1]);
    }

    else if (rc == 0) {                                                       //child created    
        printf("I am child(pid:%d)\n", (int) getpid());
        read(fd2[0], cmdinput, 100);
        printf("I read:%s\n", cmdinput);
        close(fd2[0]);
    }

    else {
        int rc_wait = wait(NULL);
        printf("I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }   

    return 0; 
}