#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include <string>
#include <vector>
#include <iostream>		// for cout program in test evaluate function
#include <unistd.h>		// for fork, execvp, stat
#include <stdio.h>		// for perror (fork error checking)
#include <cstring>		// for strcpy
#include <sys/stat.h>	// for stat
#include <sys/types.h>	// for stat

using namespace std;

class TestCommand : public Command {
	
	protected:
		
		// Inherited from Command class:
		// char** args;
		// int args_num;
		// bool success;
		// bool execute;
		char* flag;
		char* path;
	
	public:
		
		// Constructors
		TestCommand() {}
		
		TestCommand(char** arguments, int args_num)
		 : Command(arguments, args_num), flag(NULL), path(NULL) {}
		
		TestCommand(char** arguments, char* path)
		 : Command(arguments), flag((char*)"-e"), path(path) {}
		 
		TestCommand(char** arguments, char* flag, char* path)
		 : Command(arguments), flag(flag), path(path) {}
		 
		 ~TestCommand() {
		 	delete flag;
		 	delete path;
		 }
	
		// Main evaluate function
		void evaluate() {
			
			if (getExecute()) {
								
				if (getArgsNum() == 1) {
					setSuccess(0);
					cout << "(False)\n";
					return;
				}
				
				struct stat buf;
				
				if(stat(path, &buf) == -1) {
					// Path doesn't exist:
					setSuccess(0);
					cout << "(False)\n";
					return;
				}
				else {
					// Path exists, flag is -e:
					if (strcmp(flag, (char*)"-e") == 0) {
						setSuccess(1);
						cout << "(True)\n";
						return;
					}
					// Path exists, flag is -d:
					else if (strcmp(flag, (char*)"-d") == 0) {
						if(S_ISDIR(buf.st_mode)) {
							// Path is a directory
							setSuccess(1);
							cout << "(True)\n";
							return;
						}
						else {
							// Path is not a directory
							setSuccess(0);
							cout << "(False)\n";
							return;
						}
					}
					// Path exists, flag is -f
					else if (strcmp(flag, (char*)"-f") == 0) {
						if(S_ISREG(buf.st_mode)) {
							// Path is regular file
							setSuccess(1);
							cout << "(True)\n";
							return;
						}
						else {
							// Path is not a regular file
							setSuccess(0);
							cout << "(False)\n";
							return;
						}
					}
					else {
						setSuccess(0);
						cout << "Test command: Flag error\n";
						return;
					}
				}
			}
			else {
				// Did not execute command, so set success to 0 (false)
				setSuccess(0);
			}
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
		
		int getArgsNum() {
			return args_num;
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