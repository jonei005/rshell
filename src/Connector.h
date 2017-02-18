#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <iostream>

using namespace std;

class Connector : public Shell {

	protected:
		
		// leftChild should always hold a command
		Command* leftChild;

		// rightChild can hold a command or connector
		Shell* rightChild;

		// execute is used to determine whether it should execute the right child, based on left child 
		bool execute;

	public: 
		
		// Constructors
		Connector() {}
		
		Connector(Command* left)
		 : leftChild(left), rightChild(NULL), execute(1) {}
		
		Connector(Command* left, Shell* right)
		 : leftChild(left), rightChild(right), execute(1) {}
		
		Connector(Command* left, Shell* right, bool execute)
		 : leftChild(left), rightChild(right), execute(execute) {}

		void evaluate() {
			// check if left child succeeded (using leftChild->success())
			// if it succeeded, based on which connector we are in, evaluate (or don't) right child
		}

		void setLeftChild(Command* newChild) {
			leftChild = newChild;
		}

		void setRightChild(Shell* newChild) {
			rightChild = newChild;
		}
		
		void setExecute(bool newExecute) {
			execute = newExecute;
		}

		Command* getLeftChild() {
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
};

#endif
