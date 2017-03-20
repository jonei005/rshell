#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <iostream>

using namespace std;

class Connector : public Shell {

	protected:
		
		// leftChild should always hold a command
		Shell* leftChild;

		// rightChild can hold a command or connector
		Shell* rightChild;

		// execute is used to determine whether it should execute the right child, based on left child 
		bool execute;
		
		// Used to determine whether any child succeeded 
		bool anySuccess;

	public: 
		
		// Constructors
		Connector() : leftChild(NULL), rightChild(NULL), execute(1), anySuccess(0) {}
		
		Connector(Shell* left)
		 : leftChild(left), rightChild(NULL), execute(1), anySuccess(0) {}
		
		Connector(Shell* left, Shell* right)
		 : leftChild(left), rightChild(right), execute(1), anySuccess(0) {}
		
		Connector(Shell* left, Shell* right, bool execute)
		 : leftChild(left), rightChild(right), execute(execute), anySuccess(0) {}
		 
		 ~Connector() {
		 	cout << "Deleting CONNECTOR object" << endl;
		 	delete leftChild;
		 	delete rightChild;
		 }

		void evaluate() {
			// check if left child succeeded (using leftChild->success())
			// if it succeeded, based on which connector we are in, evaluate (or don't) right child
		}

		void setLeftChild(Shell* newChild) {
			leftChild = newChild;
		}

		void setRightChild(Shell* newChild) {
			rightChild = newChild;
		}
		
		void setExecute(bool newExecute) {
			execute = newExecute;
		}

		Shell* getLeftChild() {
			return leftChild;
		}

		Shell* getRightChild() {
			return rightChild;
		}
		
		bool getExecute() {
			return execute;
		}

		bool succeeded() {
			return leftChild->succeeded();
		}
		
		bool getAnySuccess() {
			return anySuccess;
		}
		
		void setAnySuccess(bool newSuccess) {
			anySuccess = newSuccess;
			return;
		}
		
		bool is_parentheses() {
			return false;
		}
		
		char** getArgs() {
			return leftChild->getArgs();
		}
};

#endif
