#ifndef SEMICOLON_H
#define SEMICOLON_H

class Semicolon : public Connector {

	// Inherited from Connector:
	// Command* leftChild, Shell* rightChild, bool execute, bool anySuccess

	public: 
		
		// Constructors
		Semicolon() : Connector() {}
		
		Semicolon(Shell* left)
		 : Connector(left) {}
		
		Semicolon(Shell* left, Shell* right)
		 : Connector(left, right) {}
		
		Semicolon(Shell* left, Shell* right, bool execute)
		 : Connector(left, right, execute) {}
		 
		 ~Semicolon() {
		 	delete leftChild;
		 	delete rightChild;
		 }

		void evaluate() {
			// no matter what left child does, evaluate right child

			leftChild->setExecute(execute);
			leftChild->evaluate();		
			
			// regardless of leftChild->execute(), execute rightChild
			rightChild->setExecute(1);			
			rightChild->evaluate();
			
			if (leftChild->getAnySuccess() || rightChild->getAnySuccess()) {
				setAnySuccess(1);
			}
			
			return;			
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
};
#endif