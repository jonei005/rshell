#ifndef INPUT_REDIRECTOR_H
#define INPUT_REDIRECTOR_H

#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

class InputRedirector : public Redirector {
    
    protected:
        
    public:
        // Constructors
        InputRedirector()
            : Redirector() {}
            
        InputRedirector(char** command, char* filename) 
            : Redirector(command, filename) {}
            
        void evaluate() {
            
            pid_t pid = fork();
            int execStatus = 0;
            
	        if(pid == -1) {
	            perror("fork");
	        } else if (pid == 0) {
	            
	            // save standard output into variable to be restored later
                int stdin = dup(0);
	        
                int inputRedirect;

                // open input and output files
                inputRedirect = open(filename, O_RDONLY);
                
                // replace standard output with output file
                dup2(inputRedirect, 0);
                close(inputRedirect);
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
            // already in a fork, just need to change stdin
            int execStatus = 0;
            
            int stdin = dup(0);
            
            int inputRedirect;
            
            inputRedirect = open(filename, O_RDONLY);
            
            dup2(inputRedirect, 0);
            close(inputRedirect);
            
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