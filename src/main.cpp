#include "Shell.h"
#include "Command.h"
#include "Connector.h"
#include "And.h"
#include "Or.h"
#include "Semicolon.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstdlib>

using namespace std;


const char* and_symbol = (char*)"&&";
const char* or_symbol = (char*)"||";
const char* semicolon = (char*)";";
bool connectorFound(char** arr, int i);

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

	
		vector<Connector*> connector_list;
		int counter = 0;
		
		//for (int i = 0; i <= args_num; ++i)
		
		for (int i = 0; exe_args[i] != NULL; i++) {
			
			if (connectorFound(exe_args, i)) {
				
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
				Command* command = new Command(command_args, col_size);
				
				// create new Connector with that command as leftChild
				if (strcmp(exe_args[i], and_symbol) == 0) {
					And* connector = new And(command);
					connector_list.push_back(connector);
				}
				else if (strcmp(exe_args[i], or_symbol) == 0) {
					Or* connector = new Or(command);
					connector_list.push_back(connector);

				}
				else if (strcmp(exe_args[i], semicolon) == 0) {
					Semicolon* connector = new Semicolon(command);
					connector_list.push_back(connector);
				}
				else {
					exit(-1);
				}
				
			}
			
			// Check for '#' to signifiy comments.
			// Set exe_args[i] = NULL to cut off the string at the comment.
			// Then break out of loop.
			else if (exe_args[i][0] == '#') {
				exe_args[i] = NULL;
				args_num = i+1;
				break;
			}
		}
		
		if (connector_list.empty()) {
			Command* command = new Command(exe_args, args_num-1);
			command->evaluate();
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
			
			Command* command = new Command(command_args, col_size);
			
			connector_list.at(connector_list.size()-1)->setRightChild(command);
			
			if (connector_list.size() >= 2) {
				for (unsigned j = 0; j < connector_list.size()-1; j++) {
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

	}
		
	return 0;
}

// checks if connector object is found at arr[i]
bool connectorFound(char** arr, int i) {
	
	if (strcmp(arr[i], and_symbol) == 0 ||
		strcmp(arr[i], or_symbol) == 0 ||
		strcmp(arr[i], semicolon) == 0)
	{ return true; }
	
	else { return false; }
}
