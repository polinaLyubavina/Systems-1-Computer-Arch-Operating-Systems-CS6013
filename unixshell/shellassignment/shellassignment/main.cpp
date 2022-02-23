#include "shelpers.hpp"
#include <readline/readline.h>
#include <iostream>
#include <stdio.h>
#include <readline/history.h>

int cd(char* path) {
    return chdir(path);
}

int main(int argc, const char * argv[]) {
    std::vector<pid_t> background; // allows background processes to run
    char* bufferReadLine; //readline autocompletes with a char* not a string
    
    // Tab completion for filepaths
    while((bufferReadLine = readline("% "))) {
        
        
        // Convert buffer to a string to be used
        std::string cmdlineInput(bufferReadLine);
//        auto symbols = tokenize(bufferReadLine);
        // Easy shell termination
        if(cmdlineInput == "quit" || cmdlineInput == "Quit" || cmdlineInput == "exit" || cmdlineInput == "Exit"){
            std::cout << "Exiting Shell" << std::endl;
            exit(0);
        }
        
        // Blank line handling
        if(cmdlineInput == "") {
            continue;
        }
    
        std::vector<std::string> tokens = tokenize(cmdlineInput);
        std::vector<Command> commands = getCommands(tokens);
        std::vector<pid_t> pids;
        
        for (int i = 0; i < commands.size(); i++) {
            // Don't go further if command is to cd or set env var
            if (commands[i].execName == "cd") {
                if (tokens.size() == 1) {
                    cd(getenv("HOME"));
                } else {
                    cd((char *)(tokens[1].c_str()));
                }
            }
            
            pid_t pid = fork();
            // Check if background process or not
            if(commands[i].background) {
                background.push_back(pid);
            } else {
                pids.push_back(pid);
            }
            
            // Forking Error
            if (pid < 0) {
                perror("Fork Error");
                exit(1);
                
            // Child process
            } else if (pid == 0) {
                int d1 = dup2(commands[i].inputFd, 0);
                int d2 = dup2(commands[i].outputFd, 1);
                if (d1 < 0 || d2 < 0) {
                    perror("File Descriptor Failure in Child Process");
                    exit(1);
                }
                for (Command c : commands) {
                    if (c.inputFd != 0) {
                        close(c.inputFd);
                    }
                    if (c.outputFd != 1) {
                        close(c.outputFd);
                    }
                }
                
                Command c = commands[i];
                if (execvp(c.execName.c_str(), const_cast<char* const *>(c.argv.data())) < 0) {
                    perror("Bad Command");
                }
            }
        }
        
        // Clean up fd stuff
        for (Command c : commands) {
            if (c.inputFd != 0) {
                close(c.inputFd);
            }
            if (c.outputFd != 1) {
                close(c.outputFd);
            }
        }

        // Wait for children to finish before moving on
        for (pid_t pid : pids) {
            int status;
            waitpid(pid, &status, 0);
            if (status < 0) {
                perror("Waiting for Children Error");
                exit(1);
            }
        }
    }
    free(bufferReadLine);
}
