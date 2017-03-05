#ifndef AND_H
#define AND_H

class And : public Connector {

	// Inherited from Connector:
	// Shell* leftChild, Shell* rightChild, bool execute, bool anySuccess

	public: 
		
		// Constructors
		And() : Connector() {}
		
		And(Shell* left)
		 : Connector(left) {}
		
		And(Shell* left, Shell* right) 
		 : Connector(left, right) {}
		
		And(Shell* left, Shell* right, bool execute)
		 : Connector(left, right, execute) {}
		 
		 // Destructor
		 ~And() {
		 	cout << "Deleting AND object" << endl;
		 	delete [] leftChild;
		 	delete [] rightChild;
		 }

		void evaluate() {
			// check if left child succeeded (using leftChild->success())
			// if succeeded, rightChild->execute = 1, evaluate 
			// if not, rightChild->execute = 0, evaluate
			
			leftChild->setExecute(execute);
			leftChild->evaluate();		
			
			// check if leftChild->evaluate() succeeded or not
			if (leftChild->succeeded()) {
				// if leftChild succeeded, set right->execute to 1, then evaluate
				rightChild->setExecute(1);				
				rightChild->evaluate();
			}
			else {
				// if leftChild failed, set right->execute to 0
				rightChild->setExecute(0);
				rightChild->evaluate();
			}
			
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