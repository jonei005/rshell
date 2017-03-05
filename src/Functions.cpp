#include "Functions.h"
#include <iostream>
#include <utility>

using namespace std;

//Function: ccFunction checks and implements all commands
void ccFunction(char** & command_args, Command* & command, int  col_size){
    // Check for '[' to signify a test command
	if (strcmp(command_args[0], "[") == 0) { //Test Command
	
		// read until ']' is found, incrementing 					
		int test_size = 0;
		while (strcmp(command_args[test_size+1], "]") != 0 && test_size < 5) {
			test_size++;
		}					
	
		if (test_size == 0) {
			// empty command, should return false
			command = new TestCommand(command_args, test_size - 1);
		}
		else if (test_size == 1) {
			// command has no flag, only path
			char* path = command_args[1];
			command = new TestCommand(command_args, path);
		}
		else if (test_size == 2) {
			// command has flag and path
			char* flag = command_args[1];
			char* path = command_args[2];
			command = new TestCommand(command_args, flag, path);
		}
		else {
			// too many arguments
			cout << "Too many arguments in [] brackets.\n";
			// probably should create a command and handle this
			// in the TestCommand->evaluate() function
		}
	}
					
	// test if first argument is "test"
	else if (strcmp(command_args[0], "test") == 0) {
		
		// Check if number of arguments is 1 (nothing after "test")
		if (col_size - 1 == 1) {
			command = new TestCommand(command_args, col_size - 1);
		}
		// If there is a flag, set proper flag/path variables
		else if (command_args[1][0] == '-') {
			char* flag = command_args[1];
			char* path = command_args[2];
			command = new TestCommand(command_args, flag, path);
		}
		// If there is not a flag, then set path variable 
		else {
			char* path = command_args[1];
			command = new TestCommand(command_args, path);
		}
	} //End of Test Command
	else {
		// create new Command with command_args
		command = new Command(command_args, col_size);
	}
}

// Function: findShell returns a shell pointer or root of a tree to be set as 
// the child of the parent

Shell* findShell(char** newArray) {
	// newArray is a char** with which we need to create a command. 
	// We need to parse newArray in order to to create a tree of commands and
	// connectors and return the root node of that tree.
		
	// Store index of left parentheses found in exe_args
	stack<pair<int,int> > parenStack;
	
	vector<Connector*> connector_list;

	int i = 0;	
	
	if (newArray[0][0] == '(') {
		
		Parentheses* paren = new Parentheses();
		
		pair<int,int> lastParenIndex;
	
		for (i = 0; newArray[i] != NULL; i++) {
			
			for (int j = 0; newArray[i][j] != '\0'; j++) {
				
				if (newArray[i][j] == '(') {
					parenStack.push(make_pair(i,j));
				}
				else if (newArray[i][j] == ')') {
					parenStack.pop();
					
					if (parenStack.empty()) {
						lastParenIndex = make_pair(i, j);
					}
				}
			}
		}
			
		//char* newerArray[i+1] = newArray + 1;
		
		//int counter = 0;
		
		int col_size = i + 1;
		char** newerArray = new char* [col_size];
		
		/*
		if (i == 1) {
			// ( not spaced AND one word command. Example: (ls)
			
		}
		*/
		
		if (newArray[0][1] != '\0') {
			// ( not spaced
			newerArray[0] = newArray[0] + 1;
			
		
			for (int j = 1; j < i; j++) {
				newerArray[j] = newArray[j];
			}
		
			
			if (i == 1) {
				lastParenIndex.second--;
			}
			
			newerArray[lastParenIndex.first][lastParenIndex.second] = '\0';

		}

		else {
			// ( is spaced
			newerArray[0] = newArray[1];
			
			for (int j = 1; j < i - 1; j++) {
				newerArray[j] = newArray[j + 1];
			}
			//newerArray[lastParenIndex.first - 1][lastParenIndex.second] = '\0';
			newerArray[lastParenIndex.first-1] = NULL;

		}
		newerArray[col_size-1] = NULL;
			
		paren->setChild(findShell(newerArray));
		
		return paren;
		
		
	
	}
	
	// Now newerArray stores entire string inside the parentheses
	// Need to look for connector if parenStack.empty()
	// NOTE: Print error if there's an unequal amount of parentheses
	// NOTE: Make sure next "word" after ')' is always a connector
	
	
	// counter = 0; //possible error
		
	// Store index of left parentheses found in exe_args
	// stack<pair<int,int> > parenStack;
	
	// vector<Connector*> connector_list;
	
	int counter = 0;
	
	for (int i = 0; newArray[i] != NULL; i++) {
			
		if (connectorFound(newArray, i) && parenStack.empty()) {
			
			if(i == 0)
			{
				cout << "Syntax Error" << endl;
				break;
			}
			
			// create char** array of exe_args with left side of connector
			int col_size = i - counter + 1;
			
			char** command_args = new char* [col_size];
			
			for (int j = 0; counter < i; counter++) {
				command_args[j] = newArray[counter];
				j++;
			}
			command_args[col_size-1] = NULL;
			counter++;
			
			// create new Command with command_args
			// Command* command;
			
			// ccFunction(command_args, command, col_size);
			
			Connector* connector;
			// create new Connector with a shell as a leftChild using find shell
			if (strcmp(newArray[i], (char*)"&&") == 0) {
				Shell* leftC = findShell(command_args);
				connector = new And(leftC);
			}
			else if (strcmp(newArray[i], (char*)"||") == 0) {
				Shell* leftC = findShell(command_args);
				connector = new Or(leftC);
			}
			else if (strcmp(newArray[i], (char*)";") == 0) {
				Shell* leftC = findShell(command_args);
				connector = new Semicolon(leftC);
			}
			else {
				exit(-1);
			}
			
			connector_list.push_back(connector);
			
		}
		
		// exe_args[i] is not a connector or #, check for parentheses
		else {
		    for (unsigned j = 0; newArray[i][j] != '\0'; j++) {
		        // check for left '('
		        if (newArray[i][j] == '(') {
		            parenStack.push(make_pair(i, j));
		        }
		        
		        // check for right ')'
		        if (newArray[i][j] == ')') {
		            parenStack.pop();
		        }
		    }
		}
	}
	
	// connector_list is made and filled
	
	if (connector_list.empty()) {
		    
		Command* command;
		
		int a = i + 1;
		ccFunction(newArray, command, a); //Not sure if i or i+1
		
		return command;
	}
	else {
		// connector_list.size() >= 1
		// must add the last command to be rightChild of last connector
		//int col_size = i + 1 - counter;
		unsigned col_size = i + 1 - counter;
		
		//THIS FUCKER IS CAUSING ALL OUR PROBLEMS
		
		// #0  0x0000003e18e325e5 in raise () from /lib64/libc.so.6
		// #1  0x0000003e18e33dc5 in abort () from /lib64/libc.so.6
		// #2  0x0000003e23abea7d in __gnu_cxx::__verbose_terminate_handler() ()
		//   from /usr/lib64/libstdc++.so.6
		// #3  0x0000003e23abcbd6 in ?? () from /usr/lib64/libstdc++.so.6
		// #4  0x0000003e23abcc03 in std::terminate() () from /usr/lib64/libstdc++.so.6
		// #5  0x0000003e23abcd22 in __cxa_throw () from /usr/lib64/libstdc++.so.6
		// #6  0x0000003e23abd11d in operator new(unsigned long) ()
		//   from /usr/lib64/libstdc++.so.6
		// #7  0x0000003e23abd1d9 in operator new[](unsigned long) ()
		//   from /usr/lib64/libstdc++.so.6
		// #8  0x0000000000401c17 in findShell (newArray=0x60a070) at Functions.cpp:243
		// #9  0x000000000040182a in findShell (newArray=0x60a100) at Functions.cpp:140
		// #10 0x0000000000405b9a in main () at rshell.cpp:131
		
		char** command_args = new char* [col_size];
		
		for (int j = 0; newArray[counter] != NULL; j++) {
			command_args[j] = newArray[counter];
			counter++;
		}
		
		command_args[col_size-1] = NULL;
		
		Command* command;
		//Shell* rightC = findShell(command_args);
		ccFunction(command_args,command,i+1); // could be newerArray?
		
		connector_list.at(connector_list.size() - 1)->setRightChild(command);
		
		if (connector_list.size() >= 2) {
			for (unsigned j = 0; j < connector_list.size()-1; j++) {
				//Not sure if we needed rightC in here?find
				connector_list.at(j)->setRightChild(connector_list.at(j+1));				
			}
		}
		
		return connector_list.at(0);
		
	}
	
}

// checks if connector object is found at arr[i]
bool connectorFound(char** arr, int i) {
	
	if (strcmp(arr[i], (char*)"&&") == 0 ||
		strcmp(arr[i], (char*)"||") == 0 ||
		strcmp(arr[i], (char*)";") == 0)
	{ return true; }
	
	else { return false; }
}



