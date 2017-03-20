#include "Shell.h"
#include "Command.h"
#include "Connector.h"
#include "And.h"
#include "Or.h"
#include "Semicolon.h"
#include "TestCommand.h"
#include "Parentheses.h"
#include "Redirector.h"
#include "InputRedirector.h"
#include "OutputRedirector.h"
#include "DoubleRedirector.h"
#include "Pipe.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <stack>
#include <utility>
#include "Functions.h"

using namespace std;

int main() {
		
	string line;
	cout << "Welcome to rShell!\nType \"exit\" to exit the command prompt.\n";
	while(line != "exit")
	{
		cout<< "$ ";
		getline(cin,line); 
		
		if(line == "exit") break;
		
		char* p = strtok((char*)line.c_str(), " "); //args seperated by spaces
		char** exe_args = NULL; //Execution args
		int args_num = 0;
		while (p != NULL) 
		{
			//Can store any size of args
			exe_args = static_cast<char**>(realloc(exe_args, sizeof (char*) * ++args_num)); //Allocate arg space
			exe_args[args_num-1] = p; //Store arg into array
			p = strtok(NULL, " "); //Store next arg into p
		}
		//Need to make sure extra element is NULL
		exe_args = static_cast<char**>(realloc(exe_args, sizeof (char*) * (args_num + 1)));
		exe_args[args_num] = NULL;
		args_num++;		// to account for the added NULL above

		// String is completely parsed into exe_args
		
		if (exe_args[0] == NULL || exe_args[0][0] == '#') {
			// restart while loop
			continue;
		}
	
		vector<Connector*> connector_list;
		int counter = 0;
		
		// Store index of left parentheses found in exe_args
		stack<pair<int,int> > parenStack;
		for (int i = 0; exe_args[i] != NULL; i++) {
			
			if (connectorFound(exe_args, i) && parenStack.empty()) {
				if(i == 0)
				{
					cout << "Syntax Error" << endl;
					break;
				}
				// create char** array of exe_args with left side of connector
				int col_size = i - counter + 1;
				
				char** command_args = new char* [col_size];
				
				for (int j = 0; counter < i; counter++) {
					command_args[j] = exe_args[counter];
					j++;
				}
				command_args[col_size-1] = NULL;
				counter++;
				
				// create new Command with command_args
				// Command* command;
				
				// ccFunction(command_args, command, col_size);
				
				Connector* connector; 
				// create new Connector with a shell as a leftChild using findShell
				if (strcmp(exe_args[i], (char*)"&&") == 0) {
					Shell* leftC = findShell(command_args);
					connector = new And(leftC);
				}
				else if (strcmp(exe_args[i], (char*)"||") == 0) {
					Shell* leftC = findShell(command_args);
					connector = new Or(leftC);
				}
				else if (strcmp(exe_args[i], (char*)";") == 0) {
					Shell* leftC = findShell(command_args);
					connector = new Semicolon(leftC);
				}
				else if (strcmp(exe_args[i], (char*)"|") == 0) {
					Shell* leftC = findShell(command_args);
					connector = new Pipe(leftC);
				}
				else {
					exit(-1);
				}
				//delete[] command_args;	// erroR?
				connector_list.push_back(connector);
				
			}
			
			// Check for '#' to signifiy comments.
			// Set exe_args[i] = NULL to cut off the string at the comment.
			// Then break out of loop.
			else if (exe_args[i][0] == '#') {
				exe_args[i] = NULL;
				args_num = i+1;
				break;
			}
	
			// exe_args[i] is not a connector or #, check for parentheses
			else {
			    for (unsigned j = 0; exe_args[i][j] != '\0'; j++) {
			        // check for left '('
			        if (exe_args[i][j] == '(') {
			            parenStack.push(make_pair(i, j));
			        }
			        
			        // check for right ')'
			        if (exe_args[i][j] == ')') {
			            parenStack.pop();
			        }
			    }
			}
		}
		
		// Finished parsing string and creating tree
		
		if (connector_list.empty()) {
			
			Shell* command = findShell(exe_args);
			command->evaluate();
		    
			// Command* command;
			
			// ccFunction(exe_args,command,args_num);
			
			// command->evaluate();
		}
		else {
			// there are > 0 connectors
			// must add the last command to be rightChild of last connector
			int col_size = args_num - counter;
			char** command_args = new char* [col_size];
			
			for (int j = 0; exe_args[counter] != NULL; j++) {
				command_args[j] = exe_args[counter];
				counter++;
			}
			
			command_args[col_size-1] = NULL;
			
			//Command* command;
			Shell* rightC = findShell(command_args);
			//ccFunction(command_args,command,col_size);
			
			connector_list.at(connector_list.size()-1)->setRightChild(rightC);
			
			if (connector_list.size() >= 2) {
				for (unsigned j = 0; j < connector_list.size()-1; j++) {
					//Not sure if we needed rightC in here?find
					connector_list.at(j)->setRightChild(connector_list.at(j+1));				
				}
			}
			
			try {
				connector_list.at(0)->evaluate();
			}catch(int e) {
				// exception thrown (exit command found)
				exit(0);
			}
		}
		
	//	delete[] exe_args;

	}
		
	return 0;
}


