#ifndef OUTPUT_REDIRECTOR_H
#define OUTPUT_REDIRECTOR_H

#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

class OutputRedirector : public Redirector {
    
    protected:
        // bool execute;
        // bool success;
        // char** command;
        // char* filename;
        bool doublearrow;
        
        
    public:
        // Constructors
        OutputRedirector() 
            : Redirector() {}
            
        OutputRedirector(char** command, char* filename) 
            : Redirector(command, filename), doublearrow(0) {}
            
        OutputRedirector(char** command, char* filename, bool doublearrow)
            : Redirector(command, filename), doublearrow(doublearrow) {}

            
        void evaluate() {
            
            // dup, pipe, or something like that
            // evaluate "command", redirect output to "filename"
            pid_t pid = fork();
            int execStatus = 0;
            
	        if(pid == -1) {
	            perror("fork");
	        } else if (pid == 0) {
	            
	            // save standard output into variable to be restored later
                int stdout = dup(1);
	        
                int outputRedirect;

                // open input and output files
                if (doublearrow) {
                    outputRedirect = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                }
                else {
                    outputRedirect = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                }
                
                
                // replace standard output with output file
                dup2(outputRedirect, 1);
                close(outputRedirect);
                // execute command
                execvp(command[0], command);
                perror("execvp");
                _exit(1);
	        }
	       else {
	           waitpid(pid, 0, 0);
	           free(command);
	       }
        }
        
        int pipeEvaluate() {
            // already in a fork, just need to change stdout
            int execStatus = 0;
            
            int stdout = dup(1);
            
            int outputRedirect;
            
            // open input and output files
            if (doublearrow) {
                outputRedirect = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            }
            else {
                outputRedirect = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            }
            
            dup2(outputRedirect, 1);
            close(outputRedirect);
            
            execStatus = execvp(command[0], command);
            
            return execStatus;
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
};

#endif