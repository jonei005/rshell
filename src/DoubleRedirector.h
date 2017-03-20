#ifndef DOUBLE_REDIRECTOR_H
#define DOUBLE_REDIRECTOR_H

#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

class DoubleRedirector : public Redirector {
    
    protected:
        char** command;
        char* inputFilename;
        char* outputFilename;
        bool doublearrow;
        
    public:
        // Constructors
        DoubleRedirector() 
            : Redirector() {}
            
        DoubleRedirector(char** command, char* inputFilename, char* outputFilename) 
            : Redirector(), command(command), inputFilename(inputFilename), outputFilename(outputFilename), doublearrow(0) {}
            
        DoubleRedirector(char** command, char* inputFilename, char* outputFilename, bool doublearrow)
            : Redirector(), command(command), inputFilename(inputFilename), outputFilename(outputFilename), doublearrow(doublearrow) {}

            
        void evaluate() {
            
            pid_t pid = fork();
            int execStatus = 0;
            
	        if(pid == -1) {
	            perror("fork");
	        } 
	        else if (pid == 0) {
	            
	            // save standard output/input into variable to be restored later
                int stdout = dup(1);
                int stdin = dup(0);
                
                int outputRedirect;
                int inputRedirect;
                
                inputRedirect = open(inputFilename, O_RDONLY);
                dup2(inputRedirect, 0);
                close(inputRedirect);
                
                if (doublearrow) {
                    outputRedirect = open(outputFilename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                    dup2(outputRedirect, 1);
                    close(outputRedirect);
                }
                else {
                    outputRedirect = open(outputFilename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                    dup2(outputRedirect, 1);
                    close(outputRedirect);
                }
                
                
                execvp(command[0], command);
                perror("execvp");
                setSuccess(0);
                exit(1);
	        }
	        else {
	            waitpid(pid, 0, 0);
	            free(command);
	        }
            
        }
        
        
        bool getExecute() {
            return execute;
        };
		
		void setExecute(bool newExecute) {
		    execute = newExecute;
		    return;
		}
		
		bool succeeded() {
		    return success;
		}
		
		bool getAnySuccess() {
		    return success;
		}
		
		void setSuccess(bool success1) {
		    this->success = success1;
		}
};

#endif