#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <iostream>		// for cout program in test evaluate function
#include <unistd.h>		// for fork, execvp
#include <stdio.h>		// for perror (fork error checking)
#include <sys/wait.h>	// for waitpid
#include <sys/types.h>	// for waitpid
#include <cstdlib>		// for exit
#include <cstring>		// for strcpy

using namespace std;

class Command : public Shell {
	
	protected:
		
		char** args;
		int args_num;
		bool success;
		bool execute;
	
	public:
		
		// Constructors
		Command() {}
	
		Command(char** arguments)
		 :  args(arguments), args_num(0), success(0), execute(1) {
		 }
		 
		Command(char* arguments[], int args_num)
		 : args(arguments), args_num(args_num), success(0), execute(1) {}
		 
		 ~Command() {
		 	delete args;
		 }
			
		// Main evaluate function
		virtual void evaluate() {
			
			if (getExecute()) {
				
				// if args is null, just return
				if (args[0] == NULL) {
					return;
				}
				
				// if args[0] == "exit", exit the program
				if (strcmp(args[0], (char*)"exit") == 0) {
					//exit(0);
					throw 99;
				}
				
				int execStatus = 0;
								
				pid_t pid = fork();

				if (pid == 0) {
					// child
					
					execStatus = execvp(args[0], args);

					// if execvp returned -1, error has occurred
					// set success variable based on this value
					if (execStatus == -1) {
						perror("execvp error");
						setSuccess(0);
					}
				}
				else {
					// parent
					
					// if wait returns error, exit
					if (waitpid(-1, NULL, 0) == -1) {
						perror("waitpid error");
						exit(-1);
					}
					
					// if execvp returned -1, print error, success = 0
					if (execStatus == -1) {
						perror("execvp error");
						setSuccess(0);
					}
					// if execvp did not return anything, then success = 1
					else {
						setSuccess(1);
					}
				}
			}
			else {
				// execute was false, command didn't run
				// set succeed to 0, do nothing else
				setSuccess(0);
			}
		}
		
		int pipeEvaluate() {
			// we are already in a fork process, only have to run execvp
			int execStatus = 0;
			execStatus = execvp(args[0], args);
			return execStatus;
		}
		
		// Setters and getters
		char* getProgram() {
			return args[0];
		}
		
		void setProgram(char* newProgram) {
			args[0] = newProgram;
		}
		
		char** getArgs() {
			return args;
		}
		
		bool succeeded() {
			return success;
		}
		
		void setSuccess(bool newSuccess) {
			success = newSuccess;
		}
		
		bool getExecute() {
			return execute;
		}
		
		void setExecute(bool newExecute) {
			execute = newExecute;
		}
		
		bool getAnySuccess() {
			return this->succeeded();
		}


};

#endif