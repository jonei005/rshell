#ifndef PARENTHESES_H
#define PARENTHESES_H

#include <iostream>

using namespace std;

class Parentheses : public Shell {

	protected:
		
		// child stores what is INSIDE the parentheses
		// Parentheses only stores one child: Command, Connector, Parentheses...
		// Of course, this child may have multpile layers of children:
		// Example: (echo hello world); child = Command(echo hello world) 
		Shell* child;

		// Used to determine whether it should execute the child.
		// This is based on previous connectors, but should be true as default
		bool execute;
		
		// Used to determine whether the parentheses succeeded/failed.
		// If any child succeeded, then the parentheses succeeded. 
		bool success;

	public:
	
		// Constructors
		Parentheses() : child(NULL), execute(1), success(0) {}
		
		Parentheses(Shell* newChild)
		 : child(newChild), execute(1), success(0) {}
		
		Parentheses(Shell* newChild, bool newExecute) 
		 : child(newChild), execute(newExecute), success(0) {}
		 
		 ~Parentheses() {
		 	cout << "Deleting parentheses object" << endl;
		 	delete child;
		 }
		
		// Main evaluate function		
		void evaluate() {
			 
			if (getExecute()) {
				
				//cout << "Evaluating parentheses object!" << endl;
				// Set child's execute bool to same value as this->execute.
				child->setExecute(execute);
				
				// Evaluate child
				child->evaluate();
				
				if (child->getAnySuccess()) {
					setSuccess(1);
				}
			}
			else {
				setSuccess(0);
			}
			
			return;			
		}
		
		// Getters & Setters
		bool getExecute() {
			return execute;			
		}
		
		void setExecute(bool newExecute) {
			execute = newExecute;
			return;			
		}
		
		bool succeeded() {
			return success;
		}
		
		void setSuccess(bool newSuccess) {
			success = newSuccess;
			return;
		}
		
		Shell* getChild() {
			return child;
		}
		
		void setChild(Shell* newChild) {
			child = newChild;
			return;
		}
		
		void setRightChild(Shell* newChild) {
			child = newChild;
			return;
		}
		
		bool getAnySuccess() {
			return success;
		}
		
		bool is_parentheses() {
			return true;
		}


};

#endif
